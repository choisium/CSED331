#include <iostream>
#include <algorithm>
using namespace std;

typedef struct {
    int length;
    unsigned int total;
    unsigned int used;
} BLOCK;

int check_possibility(int box[], BLOCK blocks[], int n) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            if (blocks[j].total == blocks[j].used) continue;
            if (box[i] % blocks[j].length != 0) return -1;
            break;
        }
    }
    return 0;
}

void print_blocks(BLOCK blocks[], int n) {
    printf("blocks: ");
    for (int i = 0; i < n; i++) {
        printf("%d: %d / %d, ", blocks[i].length, blocks[i].used, blocks[i].total);
    }
    printf("\n");
}

int stacking_blocks(int box[], BLOCK blocks[], int n) {
    // check if smaller block is needed (like 1)
    sort(box, box + 3);
    if (check_possibility(box, blocks, n) == -1) return -1;

    int largest_block_idx = n;
    for (int i = n - 1; i >= 0; i--) {
        if (blocks[i].total > blocks[i].used && blocks[i].length <= box[0]) {
            largest_block_idx = i;
            break;
        }
    }
    // there's no available blocks
    if (largest_block_idx == n) return -1;

    BLOCK& largest_block = blocks[largest_block_idx];

    int used[3] = {0};
    for (int i = 0; i < 3; i++) {
        used[i] = box[0] / largest_block.length;
    }
    largest_block.used += used[0] * used[1] * used[2];
    int new_box1[3] = {
        box[0] - largest_block.length * used[0],
        box[1],
        box[2],
    };
    int new_box2[3] = {
        largest_block.length * used[0],
        box[1] - largest_block.length * used[1],
        box[2],
    };
    int new_box3[3] = {
        largest_block.length * used[0],
        largest_block.length * used[1],
        box[2] - largest_block.length * used[2],
    };

    if (new_box1[0] && stacking_blocks(new_box1, blocks, n) == -1) return -1;
    if (new_box2[1] && stacking_blocks(new_box2, blocks, n) == -1) return -1;
    if (new_box3[2] && stacking_blocks(new_box3, blocks, n) == -1) return -1;

    return 0;
}

int main() {
    // get the number of testcases
    int t;
    scanf("%d", &t);

    BLOCK blocks[19];
    int box[3];
    int n;
    
    for(int i = 0; i < t; i++) {
        // get the number of blocks
        scanf("%d", &n);

        // get each element of the array
        for (int j = 0; j < n; j++) {
            scanf("%d", &blocks[j].length);
            blocks[j].used = 0;
        }
        for (int j = 0; j < n; j++) {
            scanf("%d", &blocks[j].total);
        }
        for (int j = 0; j < 3; j++) {
            scanf("%d", &box[j]);
        }
        int res = stacking_blocks(box, blocks, n);
        if (res == -1) {
            printf("%d\n", res);
        } else {
            printf("%d", blocks[0].used);
            for (int j = 1; j < n; j++) {
                printf(" %d", blocks[j].used);
            }
            printf("\n");
        }
    }
}