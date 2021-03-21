#include <stdio.h>
#include <stdlib.h>


int main(){
    int i, n;
    int *pData;
    printf("Enter #:");
    scanf("%d", &i);
    pData = (int *) calloc(i, sizeof(int));

    if (pData == NULL) exit (1);

    for (n=0; n < i; n++){
        printf("#%d:", n+1);
        scanf("%d", &pData[n]);
    }

    printf("Entery: ");
    for (n=0; n<i; n++){
        printf("%d ", pData[n]);
    }
    printf("\n");

    free(pData);
}
