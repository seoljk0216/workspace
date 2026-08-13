/* ============================================================
 *  허프만 코딩 텍스트 압축기 (유니코드 문자 단위)
 *  컴파일: gcc main.c -o huffman
 *  실행:   ./huffman     (윈도우는 huffman.exe)
 * ============================================================ */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_TEXT    10000   /* 입력 텍스트 최대 바이트 길이 */
#define MAX_SYMBOLS 4096    /* 서로 다른 문자(코드포인트) 최대 개수 */
/* 코드 포인트는 컴퓨터가 텍스트를 표현하기 위해 문자에 할당한 고유한 정수값 */

/* ------------------------------------------------------------
 *  0) UTF-8  <->  코드포인트 변환
 * ------------------------------------------------------------ */

/* 문자열 s의 맨 앞 한 글자를 코드포인트로 디코딩한다.
   *cp 에 코드포인트를 넣고, 그 글자가 차지한 바이트 수를 반환한다. */
static int utf8Decode(const unsigned char* s, uint32_t* cp) {
    unsigned char c = s[0];
    if (c < 0x80) {                  /* 0xxxxxxx : 1바이트 (ASCII) */
        *cp = c;
        return 1;
    } else if ((c & 0xE0) == 0xC0) { /* 110xxxxx : 2바이트 */
        *cp = ((uint32_t)(c & 0x1F) << 6)
            |  (uint32_t)(s[1] & 0x3F);
        return 2;
    } else if ((c & 0xF0) == 0xE0) { /* 1110xxxx : 3바이트 */
        *cp = ((uint32_t)(c & 0x0F) << 12)
            | ((uint32_t)(s[1] & 0x3F) << 6)
            |  (uint32_t)(s[2] & 0x3F);
        return 3;
    } else if ((c & 0xF8) == 0xF0) { /* 11110xxx : 4바이트 (이모지 등) */
        *cp = ((uint32_t)(c & 0x07) << 18)
            | ((uint32_t)(s[1] & 0x3F) << 12)
            | ((uint32_t)(s[2] & 0x3F) << 6)
            |  (uint32_t)(s[3] & 0x3F);
        return 4;
    }
    *cp = c;        /* 잘못된 바이트는 1바이트로 취급 */
    return 1;
}

/* 코드포인트 하나를 UTF-8 바이트열로 인코딩한다.
   buf(최소 4바이트)에 써넣고 쓴 바이트 수를 반환한다. */
static int utf8Encode(uint32_t cp, unsigned char* buf) {
    if (cp < 0x80) {
        buf[0] = (unsigned char)cp;
        return 1;
    } else if (cp < 0x800) {
        buf[0] = (unsigned char)(0xC0 | (cp >> 6));
        buf[1] = (unsigned char)(0x80 | (cp & 0x3F));
        return 2;
    } else if (cp < 0x10000) {
        buf[0] = (unsigned char)(0xE0 | (cp >> 12));
        buf[1] = (unsigned char)(0x80 | ((cp >> 6) & 0x3F));
        buf[2] = (unsigned char)(0x80 | (cp & 0x3F));
        return 3;
    } else {
        buf[0] = (unsigned char)(0xF0 | (cp >> 18));
        buf[1] = (unsigned char)(0x80 | ((cp >> 12) & 0x3F));
        buf[2] = (unsigned char)(0x80 | ((cp >> 6) & 0x3F));
        buf[3] = (unsigned char)(0x80 | (cp & 0x3F));
        return 4;
    }
}

/* ------------------------------------------------------------
 *  1) 허프만 트리의 노드
 *     - 잎(leaf) 노드 : 실제 문자(ch=코드포인트)와 빈도(freq)를 가진다.
 *     - 내부 노드     : 문자는 의미 없고 두 자식의 빈도 합을 가진다.
 *     - seq           : 생성 순서. 동률(tie) 처리를 결정적으로 만들기 위함.
 * ------------------------------------------------------------ */
typedef struct Node {
    uint32_t ch;           /* 코드포인트 (잎 노드에서만 의미 있음) */
    int freq;              /* 빈도 (또는 두 자식 빈도의 합) */
    int seq;               /* 생성 순서 (tie-break 용) */
    struct Node *left;     /* 왼쪽 자식 (코드 0) */
    struct Node *right;    /* 오른쪽 자식 (코드 1) */
} Node;

/* 노드 하나를 새로 만든다 */
Node* createNode(uint32_t ch, int freq, int seq, Node* left, Node* right) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->ch = ch;
    node->freq = freq;
    node->seq = seq;
    node->left = left;
    node->right = right;
    return node;
}

/* 잎 노드인지 검사 (자식이 둘 다 없으면 잎) */
int isLeaf(Node* n) {
    return n->left == NULL && n->right == NULL;
}

/* ------------------------------------------------------------
 *  2) 최소 힙 (우선순위 큐)  +  tie-break 규칙
 *     비교 기준:
 *       (1) 빈도가 작은 노드 우선
 *       (2) 빈도가 같으면 생성 순서(seq)가 빠른 노드 우선
 *     -> 같은 입력이면 항상 같은 트리/코드가 나온다.
 * ------------------------------------------------------------ */
typedef struct {
    Node* data[MAX_SYMBOLS * 2]; /* 잎 n개 + 내부 n-1개 < 2n */
    int size;
} MinHeap;

/* a가 b보다 "먼저 꺼내야 할(더 작은)" 노드면 1 */
int nodeLess(Node* a, Node* b) {
    if (a->freq != b->freq) return a->freq < b->freq;  /* (1) 빈도 */
    return a->seq < b->seq;                            /* (2) 생성 순서 */
}

void swapNode(Node** a, Node** b) {
    Node* t = *a; *a = *b; *b = t;
}

/* 힙에 노드를 넣는다 (위로 올라가며 제자리 찾기) */
void heapPush(MinHeap* h, Node* node) {
    int i = h->size++;
    h->data[i] = node;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (!nodeLess(h->data[i], h->data[parent])) break;
        swapNode(&h->data[parent], &h->data[i]);
        i = parent;
    }
}

/* 힙에서 가장 작은 노드를 꺼낸다 (아래로 내려가며 제자리 찾기) */
Node* heapPop(MinHeap* h) {
    Node* min = h->data[0]; 
    h->data[0] = h->data[--h->size];
    int i = 0;
    while (1) {
        int l = 2 * i + 1, r = 2 * i + 2, smallest = i;
        if (l < h->size && nodeLess(h->data[l], h->data[smallest])) smallest = l;
        if (r < h->size && nodeLess(h->data[r], h->data[smallest])) smallest = r;
        if (smallest == i) break;
        swapNode(&h->data[i], &h->data[smallest]);
        i = smallest;
    }
    return min;
}

/* ------------------------------------------------------------
 *  3) 허프만 트리 만들기
 *     (1) 각 문자마다 잎 노드를 만들어 힙에 넣는다.
 *         - 잎의 seq 는 "코드포인트 오름차순 순위"로 정한다.
 *           (어떤 순서로 입력돼도 결과가 항상 같도록)
 *     (2) 힙에서 가장 작은 두 노드를 꺼내(작은 쪽=left=0, 큰 쪽=right=1)
 *         부모로 합친다. 부모의 seq 는 잎 다음 번호부터 차례로.
 *     (3) 노드가 하나 남을 때까지 반복 -> 그 노드가 뿌리.
 * ------------------------------------------------------------ */
Node* buildHuffmanTree(uint32_t symCp[], int symFreq[], int nSym) {
    MinHeap heap;
    heap.size = 0;

    if (nSym == 0) return NULL;

    int seqCounter = 0;
    for (int i = 0; i < nSym; i++) {
        /* 코드포인트 오름차순 순위 = 자기보다 작은 코드포인트의 개수 */
        int rank = 0;
        for (int j = 0; j < nSym; j++)
            if (symCp[j] < symCp[i]) rank++;
        heapPush(&heap, createNode(symCp[i], symFreq[i], rank, NULL, NULL));
        (void)seqCounter;
    }
    seqCounter = nSym;  /* 내부 노드의 seq 는 잎 다음 번호부터 */

    while (heap.size > 1) {
        Node* a = heapPop(&heap);   /* 가장 작은 노드 -> 왼쪽(0) */
        Node* b = heapPop(&heap);   /* 두 번째 노드   -> 오른쪽(1) */
        Node* parent = createNode(0, a->freq + b->freq, seqCounter++, a, b);
        heapPush(&heap, parent);
    }

    return heapPop(&heap);
}

/* ------------------------------------------------------------
 *  4) 코드표 만들기
 *     뿌리에서 잎까지 내려가며 왼쪽=0, 오른쪽=1 을 붙인다.
 *     잎에 도착하면 그 문자(코드포인트)에 해당하는 심볼 칸에 코드를 저장.
 * ------------------------------------------------------------ */
void generateCodes(Node* root, char* code, int depth,
                   uint32_t symCp[], char* symCode[], int nSym) {
    if (root == NULL) return;

    if (isLeaf(root)) {
        /* 이 잎의 코드포인트가 심볼 목록 몇 번인지 찾는다 */
        int idx = 0;
        for (int j = 0; j < nSym; j++)
            if (symCp[j] == root->ch) { idx = j; break; }

        if (depth == 0) {
            /* 문자가 딱 한 종류뿐이면 코드가 비어버린다. "0" 으로 정해 준다. */
            symCode[idx] = strdup("0");
        } else {
            code[depth] = '\0';
            symCode[idx] = strdup(code);
        }
        return;
    }

    code[depth] = '0';
    generateCodes(root->left, code, depth + 1, symCp, symCode, nSym);

    code[depth] = '1';
    generateCodes(root->right, code, depth + 1, symCp, symCode, nSym);
}

/* 트리 메모리 해제 */
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

/* 심볼 목록에서 코드포인트 cp 의 칸 번호를 찾는다 */
int findSym(uint32_t symCp[], int nSym, uint32_t cp) {
    for (int j = 0; j < nSym; j++)
        if (symCp[j] == cp) return j;
    return -1;
}

/* 화면 출력 : 안 보이는 글자는 이름으로, 그 외에는 실제 문자로 */
void printChar(uint32_t cp) {
    if (cp == ' ')       { printf("'공백'"); return; }
    if (cp == '\n')      { printf("'줄바꿈'"); return; }
    if (cp == '\t')      { printf("'탭'");   return; }

    unsigned char buf[5];
    int n = utf8Encode(cp, buf);
    buf[n] = '\0';
    printf("%s", buf);    /* 한글 등 실제 문자 그대로 출력 */
}

/* ------------------------------------------------------------
 *  각 섹션을 따로 출력하는 함수들
 *  (계산은 runHuffman에서 끝내고, 결과만 받아서 출력한다)
 * ------------------------------------------------------------ */

/* [1] 문자별 빈도 & 허프만 코드표 */
void printSectionTable(uint32_t symCp[], int symFreq[], char* symCode[], int nSym) {
    printf("\n============================================================\n");
    printf("  [1] 문자별 빈도 & 허프만 코드표\n");
    printf("============================================================\n");
    printf("  문자    빈도   허프만 코드\n");
    printf("  ------------------------------------\n");
    for (int i = 0; i < nSym; i++) {
        printf("  ");
        printChar(symCp[i]);
        printf("\t%4d    %s\n", symFreq[i], symCode[i]);
    }
}

/* [2] 실제 압축된 데이터 (16진수 바이트) */
void printSectionPacked(unsigned char* packed, int byteCount) {
    printf("\n============================================================\n");
    printf("  [2] 실제 압축된 데이터 (16진수 바이트)\n");
    printf("============================================================\n  ");
    for (int i = 0; i < byteCount; i++) {
        printf("%02X ", packed[i]);
        if ((i + 1) % 16 == 0) printf("\n  ");
    }
    printf("\n");
}

/* [3] 압축 결과 분석 */
void printSectionAnalysis(char* symCode[], int nSym,
                          int charLen, int byteLen, long totalBits, int byteCount) {
    long originalBits = (long)byteLen * 8;   /* 원본 UTF-8 크기 (실제 저장 크기) */
    double ratio = (1.0 - (double)totalBits / originalBits) * 100.0;

    /* 코드표까지 함께 저장한다고 가정할 때의 크기 */
    long tableBits = 0;
    for (int i = 0; i < nSym; i++) {
        tableBits += 32;                        /* 문자(코드포인트) 32비트 */
        tableBits += 8;                         /* 코드 길이 */
        tableBits += (long)strlen(symCode[i]);  /* 코드 비트 */
    }
    long totalWithTable = totalBits + tableBits;
    double ratioWithTable = (1.0 - (double)totalWithTable / originalBits) * 100.0;

    printf("\n============================================================\n");
    printf("  [3] 압축 결과 분석\n");
    printf("============================================================\n");
    printf("  전체 문자 수      : %d 자\n", charLen);
    printf("  서로 다른 문자    : %d 종류\n", nSym);
    printf("  ------------------------------------------------------------\n");
    printf("  원본 크기 (UTF-8) : %ld 비트  (= %d 바이트)\n", originalBits, byteLen);
    printf("  압축 후 (데이터)  : %ld 비트  (= %d 바이트)\n", totalBits, byteCount);
    printf("  코드표 포함 시     : %ld 비트\n", totalWithTable);
    printf("  압축률(데이터)    : %.1f%% 절약\n", ratio);
    printf("  압축률(표 포함)   : %.1f%% 절약", ratioWithTable);
}

/* [4] 복원(압축 해제) 결과 + 검증 */
void printSectionDecoded(Node* root, const char* text, unsigned char* packed,
                         long totalBits, int charLen, int byteLen) {
    char* decoded = (char*)malloc(byteLen + 1);
    int outLen = 0;        /* decoded 에 쓴 바이트 수 */
    int produced = 0;      /* 복원한 문자 수 */

    if (isLeaf(root)) {
        /* 문자가 한 종류뿐인 경우 */
        for (int i = 0; i < charLen; i++) {
            unsigned char buf[5];
            int n = utf8Encode(root->ch, buf);
            for (int k = 0; k < n; k++) decoded[outLen++] = (char)buf[k];
            produced++;
        }
    } else {
        Node* cur = root;
        for (long i = 0; i < totalBits && produced < charLen; i++) {
            int bit = (packed[i / 8] >> (7 - (i % 8))) & 1;
            cur = bit ? cur->right : cur->left;
            if (isLeaf(cur)) {
                unsigned char buf[5];
                int n = utf8Encode(cur->ch, buf);   /* 코드포인트 -> UTF-8 바이트 */
                for (int k = 0; k < n; k++) decoded[outLen++] = (char)buf[k];
                produced++;
                cur = root;
            }
        }
    }
    decoded[outLen] = '\0';

    printf("\n============================================================\n");
    printf("  [4] 복원(압축 해제) 결과\n");
    printf("============================================================\n");
    printf("  복원된 텍스트: %s\n", decoded);
    if (strcmp(text, decoded) == 0)
        printf("  검증 결과    : 원본과 100%% 일치\n");
    else
        printf("  검증 결과    : 불일치 (오류 발생)\n");
    printf("============================================================\n");

    free(decoded);
}

/* ============================================================
 *  메인 처리: 텍스트 하나를 받아 전체 과정을 수행
 *  계산을 모두 끝낸 뒤, 사용자가 고른 섹션만 반복 출력한다.
 * ============================================================ */
void runHuffman(const char* text) {
    int byteLen = (int)strlen(text);
    if (byteLen == 0) {
        printf("\n[알림] 입력된 텍스트가 없습니다.\n");
        return;
    }

    /* (0) UTF-8 -> 코드포인트 배열 (문자 단위 시퀀스) */
    uint32_t cps[MAX_TEXT];
    int charLen = 0;
    {
        const unsigned char* p = (const unsigned char*)text;
        int i = 0;
        while (i < byteLen && charLen < MAX_TEXT) {
            uint32_t cp;
            int n = utf8Decode(p + i, &cp);
            cps[charLen++] = cp;
            i += n;
        }
    }

    /* (1) 빈도 분석: 서로 다른 코드포인트를 등장 순서대로 모은다 */
    uint32_t symCp[MAX_SYMBOLS];
    int symFreq[MAX_SYMBOLS];
    int nSym = 0;
    for (int i = 0; i < charLen; i++) {
        int idx = findSym(symCp, nSym, cps[i]);
        if (idx >= 0) {
            symFreq[idx]++;
        } else if (nSym < MAX_SYMBOLS) {
            symCp[nSym] = cps[i];
            symFreq[nSym] = 1;
            nSym++;
        }
    }

    /* (2) 허프만 트리 (tie-break는 buildHuffmanTree 안에서 처리) */
    Node* root = buildHuffmanTree(symCp, symFreq, nSym);

    /* (3) 코드표 */
    char* symCode[MAX_SYMBOLS] = {0};
    char buffer[MAX_SYMBOLS + 1];
    generateCodes(root, buffer, 0, symCp, symCode, nSym);

    /* (4) 실제 압축: 문자별 코드를 이어붙여 비트로 만들고 바이트에 채운다 */
    long totalBits = 0;
    for (int i = 0; i < charLen; i++) {
        int idx = findSym(symCp, nSym, cps[i]);
        totalBits += (long)strlen(symCode[idx]);
    }

    int byteCount = (int)((totalBits + 7) / 8);
    unsigned char* packed = (unsigned char*)calloc(byteCount > 0 ? byteCount : 1, 1);

    long bitPos = 0;
    for (int i = 0; i < charLen; i++) {
        int idx = findSym(symCp, nSym, cps[i]);
        char* code = symCode[idx];
        for (int j = 0; code[j] != '\0'; j++) {
            if (code[j] == '1')
                packed[bitPos / 8] |= (unsigned char)(1 << (7 - (bitPos % 8)));
            bitPos++;
        }
    }

    /* (5) 어떤 결과를 볼지 골라서 출력 (원하는 것만) */
    char sel[64];
    while (1) {
        printf("\n------------------------------------------------------------\n");
        printf("  어떤 결과를 보시겠습니까?\n");
        printf("    1. 문자별 빈도 & 허프만 코드표\n");
        printf("    2. 실제 압축된 데이터 (16진수)\n");
        printf("    3. 압축 결과 분석\n");
        printf("    4. 복원(압축 해제) 결과\n");
        printf("    0. 메인 메뉴로 돌아가기\n");
        printf("  선택 > ");
        fflush(stdout);

        if (!fgets(sel, sizeof(sel), stdin)) break;

        if (sel[0] == '0') break;

        switch (sel[0]) {
            case '1': printSectionTable(symCp, symFreq, symCode, nSym); break;
            case '2': printSectionPacked(packed, byteCount); break;
            case '3': printSectionAnalysis(symCode, nSym, charLen, byteLen, totalBits, byteCount); break;
            case '4': printSectionDecoded(root, text, packed, totalBits, charLen, byteLen); break;
            default:  printf("\n[알림] 0~4 중에서 입력하세요.\n"); break;
        }
    }

    /* 메모리 정리 */
    for (int i = 0; i < nSym; i++) if (symCode[i]) free(symCode[i]);
    free(packed);
    freeTree(root);
}

int main(void) {
    char line[1024];

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    /* UTF-8 콘솔에서 멀티바이트(한글)가 쪼개져 깨지는 것을 막는다. */
    setvbuf(stdout, NULL, _IOFBF, 1 << 16);
#endif

    while (1) {
        printf("\n############################################################\n");
        printf("#                                                          #\n");
        printf("#          허프만 코딩 텍스트 압축기  (Huffman)                #\n");
        printf("#                                                          #\n");
        printf("############################################################\n");
        printf("  1. 새 텍스트 압축하기\n");
        printf("  2. 종료\n");
        printf("------------------------------------------------------------\n");
        printf("  선택 > ");
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin)) break;

        if (line[0] == '2') {
            printf("\n프로그램을 종료합니다.\n");
            break;
        }
        if (line[0] != '1') {
            printf("\n[알림] 1 또는 2를 입력하세요.\n");
            continue;
        }

        printf("\n압축할 텍스트를 입력하세요. (입력을 끝내려면 마지막 줄에 점(.) 하나만 입력)\n");
        printf("------------------------------------------------------------\n");

        char text[MAX_TEXT];
        text[0] = '\0';

        fflush(stdout);
        while (fgets(line, sizeof(line), stdin)) {
            if (strcmp(line, ".\n") == 0 || strcmp(line, ".") == 0) break;
            if (strlen(text) + strlen(line) < MAX_TEXT - 1) {
                strcat(text, line);
            } else {
                printf("[알림] 텍스트가 너무 깁니다. 여기까지만 처리합니다.\n");
                break;
            }
        }

        int tlen = (int)strlen(text);
        if (tlen > 0 && text[tlen - 1] == '\n') text[tlen - 1] = '\0';

        runHuffman(text);
    }
    return 0;
}