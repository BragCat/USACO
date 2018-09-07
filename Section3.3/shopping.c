/*
 ID: bragcat1
 LANG: C
 TASK: shopping
 */

#include <stdio.h>
#include <memory.h>

#define MAX_INT 0x7fffffff;
#define MAX_PRODUCT_NUMBER 5
#define MAX_TARGET_PRODUCT_NUMBER 6
#define MAX_SPECIAL_OFFER_NUMBER 99

#define min(a,b) ((a)<(b))?(a):(b)

int specialOfferNumber, productNumber;
int specialOfferContentNumber[MAX_SPECIAL_OFFER_NUMBER];
int specialOfferContent[MAX_SPECIAL_OFFER_NUMBER][MAX_PRODUCT_NUMBER][2];
int specialOfferPrice[MAX_SPECIAL_OFFER_NUMBER];
int productCode[MAX_PRODUCT_NUMBER], targetProductNumber[MAX_PRODUCT_NUMBER], productPrice[MAX_PRODUCT_NUMBER];

void preprocess() {
    for (int i = 0; i < specialOfferNumber; ++i) {
        for (int j = 0; j < specialOfferContentNumber[i]; ++j) {
            int product = specialOfferContent[i][j][0];
            for (int k = 0; k < productNumber; ++k) {
                if (productCode[k] == product) {
                    specialOfferContent[i][j][0] = k;
                    break;
                }
            }
        }
    }
}

int dp() {
    preprocess();

    int f[MAX_TARGET_PRODUCT_NUMBER][MAX_TARGET_PRODUCT_NUMBER][MAX_TARGET_PRODUCT_NUMBER][MAX_TARGET_PRODUCT_NUMBER][MAX_TARGET_PRODUCT_NUMBER];
    for (int i0 = 0; i0 <= targetProductNumber[0]; ++i0) {
        for (int i1 = 0; i1 <= targetProductNumber[1]; ++i1) {
            for (int i2 = 0; i2 <= targetProductNumber[2]; ++i2) {
                for (int i3 = 0; i3 <= targetProductNumber[3]; ++i3) {
                    for (int i4 = 0; i4 <= targetProductNumber[4]; ++i4) {
                        f[i0][i1][i2][i3][i4] = i0 * productPrice[0] + i1 * productPrice[1] + i2 * productPrice[2]
                                + i3 * productPrice[3] + i4 * productPrice[4];
                    }
                }
            }
        }
    }
    f[0][0][0][0][0] = 0;
    for (int i = 0; i < specialOfferNumber; ++i) {
        int minProductNumber[MAX_PRODUCT_NUMBER] = {0};
        for (int j = 0; j < specialOfferContentNumber[i]; ++j) {
            minProductNumber[specialOfferContent[i][j][0]] = specialOfferContent[i][j][1];
        }
        for (int i0 = 0; i0 <= targetProductNumber[0]; ++i0) {
            for (int i1 = 0; i1 <= targetProductNumber[1]; ++i1) {
                for (int i2 = 0; i2 <= targetProductNumber[2]; ++i2) {
                    for (int i3 = 0; i3 <= targetProductNumber[3]; ++i3) {
                        for (int i4 = 0; i4 <= targetProductNumber[4]; ++i4) {
                            if (i0 >= 1) {
                                f[i0][i1][i2][i3][i4] = min(f[i0][i1][i2][i3][i4], f[i0 - 1][i1][i2][i3][i4] + productPrice[0]);
                            }
                            if (i1 >= 1) {
                                f[i0][i1][i2][i3][i4] = min(f[i0][i1][i2][i3][i4], f[i0][i1 - 1][i2][i3][i4] + productPrice[1]);
                            }
                            if (i2 >= 1) {
                                f[i0][i1][i2][i3][i4] = min(f[i0][i1][i2][i3][i4], f[i0][i1][i2 - 1][i3][i4] + productPrice[2]);
                            }
                            if (i3 >= 1) {
                                f[i0][i1][i2][i3][i4] = min(f[i0][i1][i2][i3][i4], f[i0][i1][i2][i3 - 1][i4] + productPrice[3]);
                            }
                            if (i4 >= 1) {
                                f[i0][i1][i2][i3][i4] = min(f[i0][i1][i2][i3][i4], f[i0][i1][i2][i3][i4 - 1] + productPrice[4]);
                            }
                            if (i0 >= minProductNumber[0] && i1 >= minProductNumber[1] && i2 >= minProductNumber[2] && i3 >= minProductNumber[3] && i4 >= minProductNumber[4]) {
                                f[i0][i1][i2][i3][i4] = min(f[i0][i1][i2][i3][i4],
                                        f[i0 - minProductNumber[0]][i1 - minProductNumber[1]][i2 - minProductNumber[2]][i3 - minProductNumber[3]][i4 - minProductNumber[4]] + specialOfferPrice[i]);
                            }
                        }
                    }
                }
            }
        }
    }

    return f[targetProductNumber[0]][targetProductNumber[1]][targetProductNumber[2]][targetProductNumber[3]][targetProductNumber[4]];
}

int main() {
    FILE *fin = fopen("shopping.in", "r");
    fscanf(fin, "%d", &specialOfferNumber);
    for (int i = 0; i < specialOfferNumber; ++i) {
        fscanf(fin, "%d", &specialOfferContentNumber[i]);
        for (int j = 0; j < specialOfferContentNumber[i]; ++j) {
            fscanf(fin, "%d%d", &specialOfferContent[i][j][0], &specialOfferContent[i][j][1]);
        }
        fscanf(fin, "%d", &specialOfferPrice[i]);
    }
    fscanf(fin, "%d", &productNumber);
    for (int i = 0; i < productNumber; ++i) {
        fscanf(fin, "%d%d%d", &productCode[i], &targetProductNumber[i], &productPrice[i]);
    }
    fclose(fin);

    int lowestPrice = dp();

    FILE *fout = fopen("shopping.out", "w");
    fprintf(fout, "%d\n", lowestPrice);
    fclose(fout);
    return 0;
}
