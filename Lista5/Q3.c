#include <stdio.h>
#include <stdlib.h>

int main() {
    int *nums = NULL;
    int count = 0;
    int n;

    while (scanf("%d", &n) == 1) {
        int *temp = realloc(nums, (count + 1) * sizeof(int));
        if (temp == NULL) {
            free(nums);
            return 1;
        }
        nums = temp;
        nums[count++] = n;
    }

    printf("Mais um bom dia de trabalho!\n");

    for (int i = 0; i < count; i++) {
        if (nums[i] % 2 != 0)
            printf("%d\n", nums[i]);
    }

    for (int i = 0; i < count; i++) {
        if (nums[i] % 2 == 0)
            printf("%d\n", nums[i]);
    }

    printf("Vou visitar esses lugares de novo... algum dia.\n");

    free(nums);
    return 0;
}
