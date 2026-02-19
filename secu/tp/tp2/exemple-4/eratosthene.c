#include <stdio.h>
#include <stdlib.h>

int main(){
    int n = 256;
    int tab[n];
    for(int i = 0; i<n; i++){
        tab[i] = 1;
    }
    tab[0] = 0;
    tab[1] = 0;
    for(int i = 2; i<n; i++){
        if(tab[i]){
            for(int j = i*i; j<n; j+=i){
                tab[j] = 0;
            }
        }
    }
    for(int i = 0; i<n; i++){
        if(tab[i]) printf("%d\n", i);
    }
}

