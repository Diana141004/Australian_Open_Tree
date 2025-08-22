#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    char nume[30];
    struct node * left;
    struct node * right;
};

//----------TREE-------------

struct node * create_node(char cuv[]){

    struct node * nou = NULL;
    nou = (struct node * )malloc(sizeof(struct node));
    strcpy(nou -> nume , cuv);
    nou -> left = NULL;
    nou -> right = NULL;

    return nou;

}

struct node * build_tree(struct node ** array, int l, int r){

    if(l==r) return array[l];
    int mid = (l+r)/2;

    struct node * root = create_node("???");
    root -> left = build_tree(array,l,mid);
    root -> right = build_tree(array,mid+1,r);

    return root;

}

struct node * stramos_comun(struct node* root , char c1[], char c2[]){

    if(!root) return NULL;

    if(strcmp (root -> nume, c1) == 0 || strcmp( root -> nume, c2) == 0) return root;

    struct node * left = stramos_comun(root -> left , c1,c2);
    struct node * right = stramos_comun(root -> right , c1,c2);

    if(left && right) return root;
    return (left ? left : right);

}

struct node * meci(int scor1[], int scor2[], int n, struct node * juc1, struct node * juc2){

        int n1 = 0,n2 = 0;
        for(int i = 0; i< n ;i++ )
            scor1[i] > scor2[i] ? n1++ : n2++;
            if(n1==3) return juc1;
            if(n2==3) return juc2;

}

// struct node * find_parinte(char nume1[], char nume2[], struct node * root){

//     if (!root) return NULL;

//     if( (strcmp(root -> left -> nume,nume1)==0 && strcmp(root -> right -> nume,nume2)==0) || (strcmp(root -> left -> nume,nume2)==0 && strcmp(root -> right -> nume,nume1)==0 )){
//         return root;
//     }

//     struct node* l = find_parinte(nume1,nume2, root->left);
//     if (l) return l;
//     return  find_parinte(nume1,nume2,root->right);

// }

int height(struct node * tree){

    if(!tree) return 0;
    if(!tree -> left && !tree -> right) return 1;

    int hl = height(tree -> left );
    int hr = height(tree -> right);

    return (hl > hr ? hl : hr) + 1;

}

struct node * find_node(struct node * root, int runda){

    if(!root) return NULL;
    
    if(root->left && root->right){

        if( strcmp(root -> left -> nume, "???") != 0  && 
            strcmp(root -> right -> nume, "???" )!= 0 && 
            strcmp(root->nume,"???")==0               &&
            height(root) == runda) {

            return root;

        }
}

    struct node* l = find_node(root->left,runda);
    if(l) return l;
    return find_node(root->right,runda);

}

//----------------CALCULE------------------

int calcul_games(int scor1[], int scor2[], int n){

        int games =0;

        for(int i = 0; i< n ;i++ ){
            games += scor1[i];
            games += scor2[i];
        }

        return games;
}

int log_2(int n){

    int k = 0;

    while(n>1){
        n>>=1;
        k++;
    }

    return k;

}

//-------------DISPLAY-------------

void display_1(struct node ** array){

    printf("\n");
    int i = 0;
    while(array [i]){

        printf("%s\n%s\n\n", array[i] -> nume, array[i+1] -> nume);
        i+=2;

    }

}

void display_runda(struct node * tree, int runda){

    if(tree){

        if(height(tree) == runda + 1){
            printf("%s\n%s\n\n", tree -> left -> nume, tree -> right -> nume);
        }

        display_runda(tree->left,runda);
        display_runda(tree->right,runda);

    }

}

int main(){

    int n,comanda, nr_games, j1[7],j2[7];
    char cuv[30],jucator1[30], jucator2[30];
    struct node ** frunze = {NULL}, *tree = NULL, * stramos, *castigator;
    
    printf("Astept input:"); 
    scanf("%d", &n);
    //getchar();

    frunze = calloc(2*n , sizeof(struct node));

    for(int i = 0; i < n; i++ ){
        scanf("%s", cuv);
        //getchar();
        frunze [i] = create_node(cuv);
    }

    tree = build_tree(frunze,0,n-1);

    scanf("%d", &comanda);

    switch (comanda){
    case 1:
        display_1(frunze);
        break;

    case 2:{

       // getchar();
        scanf("%s", jucator1);
        //getchar();
        scanf("%s", jucator2);

        stramos = stramos_comun(tree, jucator1, jucator2);
        printf("%d", height(stramos));

        break;
    }

    case 3:{

        for (int i=0; i<n/2; i++){

            scanf("%d", &nr_games);
            for(int j=0;j<nr_games;j++){
                scanf( "%d", &j1[j]);
            }
 
            for(int j=0;j<nr_games;j++){
                scanf( "%d", &j2[j]);
            }

            stramos = find_node(tree,2);
            castigator = meci(j1,j2,nr_games,stramos->left,stramos->right);
            strcpy(stramos -> nume, castigator -> nume);

        }

        display_runda(tree,2);

        break;
    }

    case 4:{

        struct node * pereche;
        int nr_games_max = 0;

        for (int i=0; i<n/2; i++){

            scanf("%d", &nr_games);

            for(int j=0;j<nr_games;j++){
                scanf( "%d", &j1[j]);
            }
 
            for(int j=0;j<nr_games;j++){
                scanf( "%d", &j2[j]);
            }

            stramos = find_node(tree,2);
            castigator = meci(j1,j2,nr_games,stramos->left,stramos->right);
            strcpy(stramos -> nume, castigator -> nume);

            if(calcul_games(j1,j2,nr_games) > nr_games_max) {
                nr_games_max = calcul_games(j1,j2,nr_games);
                pereche=stramos;
            }

        }

        printf("%s\n%s", pereche -> left, pereche -> right);


        break;
    }

    case 5:{

        int round = 1;
        int count = log_2(n);


        for( int k= 0; k < count ; k++) {

            n /= 2;
            round ++;
            for (int i=0; i<n; i++){

                scanf("%d", &nr_games);

                for(int j=0;j<nr_games;j++){
                    scanf( "%d", &j1[j]);
                }
    
                for(int j=0;j<nr_games;j++){
                    scanf( "%d", &j2[j]);
                }

                stramos = find_node(tree,round);
                castigator = meci(j1,j2,nr_games,stramos->left,stramos->right);
                strcpy(stramos -> nume, castigator -> nume);

            }
    }

    printf("%s", tree -> nume);

        break;
    }
    
    default:
        break;
    }

}

