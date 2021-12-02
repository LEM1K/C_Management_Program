#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void init_member();
void init_item();
void init_sales();

void print_index();
void print_manager_menu();
void print_staff_menu();
void print_inventory_menu();
void print_employee_menu();
void print_sale_menu();
void print_sales_menu();

void load_item_file();
void add_item();
void read_item();
void update_item();
void delete_item();
int search_item();

void load_member_file();
void add_member();
void read_member();
void update_member();
void delete_member();
int search_member();

void loat_sales_file();
void add_sales();
void read_sales();
void update_sales();
void remove_sales();

void inventory_menu();
void employee_menu();
void sale_menu();
void sales_menu();

int login();
int manager_menu_handler();
int staff_menu_handler();


typedef struct member {
    char id[10];
    char pw[10];
    char name[10];
    char phone[20];
    char role[10];

    struct member *next;

} MEMBER;

typedef struct inventory {
    char code[10];
    char name[20];
    char price[10];
    char count[10];
    char category[10];

    struct inventory *next;

} ITEM;

typedef struct sales {
    char name[20];
    char product_price[10];
    char sales_count[10];
    char sales_price[10000000];

    struct sales *next;
} SALES;

void init_member(MEMBER *member) {
    sprintf(member->id, "");
    sprintf(member->pw, "");
    sprintf(member->name, "");
    sprintf(member->phone, "");
    sprintf(member->role, "");

    member->next = NULL;
}

void init_item(ITEM *item) {
    sprintf(item->code, "");
    sprintf(item->name, "");
    sprintf(item->price, "");
    sprintf(item->count, "");
    sprintf(item->category, "");

    item->next = NULL;
}

void init_sales(SALES *sales) {
    sprintf(sales->name, "");
    sprintf(sales->product_price, "");
    sprintf(sales->sales_count, "");
    sprintf(sales->sales_price, "");

    sales->next = NULL;
}


void print_index() {
    printf("=================================================\n");
    printf("|================== POS 시스템 =================|\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                    1. 로그인                  |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|===============================================|\n");
    printf("=================================================\n");
    printf(">> ('0' 입력시 종료) ");
}

void load_item_file(ITEM *item, FILE *fp) {
    ITEM *tmp;
    ITEM *last;

    tmp = (ITEM *) malloc(sizeof(ITEM));

    fscanf(fp, "%s %s %s %s %s", tmp->code, tmp->name, tmp->price, tmp->count, tmp->category);
    if(feof(fp) == 0) {

        item->next = tmp;
        last = tmp;
    }
    else {
        free(tmp);
    }

    tmp = (ITEM *) malloc(sizeof(ITEM));
    fscanf(fp, "%s %s %s %s %s", tmp->code, tmp->name, tmp->price, tmp->count, tmp->category);
    if(feof(fp) == 0) {

        last->next = tmp;
        last = tmp;
    }
    else {
        free(tmp);
    }

    while(1) {
        tmp = (ITEM *) malloc(sizeof(ITEM));

        fscanf(fp, "%s %s %s %s %s", tmp->code, tmp->name, tmp->price, tmp->count, tmp->category);
        if(feof(fp) == 0) {

            last->next = tmp;
            last = tmp;
        }
        else {
            free(tmp);
            break;
        }
    }
}

void add_item(FILE *fp, ITEM *it) {

    fp = fopen("inventory.txt", "a+");
    if(fp == NULL) {
        printf("파일열기 실패.\n");
        exit(1);
    }

    ITEM* item = (ITEM*)malloc(sizeof(ITEM));
    init_item(item);

    ITEM* temp = it;
    while(temp->next != NULL) {
        temp = temp->next;
    }

    getchar();
    printf("상품 코드 : ");
    scanf("%s", item->code);
    printf("상품 이름 : ");
    scanf("%s", item->name);
    printf("상품 가격 : ");
    scanf("%s", item->price);
    printf("상품 수량 : ");
    scanf("%s", item->count);
    printf("카테고리 : ");
    scanf("%s", item->category);

    temp->next = item;

    fprintf(fp, "%s\t\t%s\t\t%s\t\t%s\t\t%s\n", item->code, item->name, item->price, item->count, item->category);

    fclose(fp);
}

void update_item(ITEM *it) {
    char code[20];
    printf("수정할 상품 코드 입력 : ");
    getchar();
    scanf("%s", code);

    ITEM* temp = it->next;
    FILE* fpw = fopen("inventory_tmp.txt", "w");

    if(fpw == NULL) {
        printf("파일 열기 실패\n");
        exit(1);
    }

    int check_count = 0;

    while(temp != NULL) {
        if(strcmp(temp->code, code) == 0) {
            check_count++;
            int select = 0;

            printf("1. 상품 코드\n");
            printf("2. 상품 이름\n");
            printf("3. 상품 가격\n");
            printf("4. 상품 수량\n");
            printf("5. 카테고리\n");
            printf("선택하세요 (선택지 이외 숫자 입력시 취소) >> ");
            scanf("%d", &select);

        
            switch(select){
                case 1: 
                    printf("수정될 상품 코드 : ");
                    getchar();
                    scanf("%s", temp->code);
                    break;
                case 2:
                    printf("수정될 상품 이름 : ");
                    getchar();
                    scanf("%s", temp->name);
                    break;
                case 3:
                    printf("수정될 상품 가격 : ");
                    getchar();
                    scanf("%s", temp->price);
                    break;
                case 4:
                    printf("수정될 상품 수량 : ");
                    getchar();
                    scanf("%s", temp->count);
                    break;
                case 5:
                    printf("수정될 카테고리 : ");
                    getchar();
                    scanf("%s", temp->category);
                    break;

                default:
                    printf("종료합니다.\n");
                    break;
            }
        }
        fprintf(fpw, "%s\t\t%s\t\t%s\t\t%s\t\t%s\n", temp->code, temp->name, temp->price, temp->count, temp->category);
        
        temp = temp->next;
        
    }
    fclose(fpw);

    if(check_count == 0) {  
        remove("inventory_tmp.txt");
    }

    else {
        remove("inventory.txt");
        rename("inventory_tmp.txt", "inventory.txt");
    }
      
}

void delete_item(ITEM *it) {
    char code[20];
    printf("삭제할 상품 코드 : ");
    getchar();
    scanf("%s", code);

    if(it == NULL) {
        printf("존재하지 않는 상품입니다.\n");
        return;
    }

    FILE* fpw = fopen("inventory_tmp.txt", "w");

    if(fpw == NULL) {
        printf("파일 열기 실패\n");
        exit(1);
    }

    ITEM *cur = it;
    ITEM *prev = NULL;

    while(cur != NULL) {
        if(strcmp(cur->code, code) == 0) {
            if(prev == NULL) {
                it->next = cur->next;
            }
            else {
                prev->next = cur->next;
            }
            free(cur);
        }

        else {
            fprintf(fpw, "%s\t\t%s\t\t%s\t\t%s\t\t%s\n", cur->code, cur->name, cur->price, cur->count, cur->category);
        }

        prev = cur;
        cur = cur->next;
    }
    fclose(fpw);
    
    remove("inventory.txt");
    rename("inventory_tmp.txt", "inventory.txt");
   
}

void read_item(ITEM *it) {
    ITEM* temp = it->next;
    printf("코드\t이름\t\t가격\t수량\t카테고리\n");
    while(temp != NULL) {
        printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\n", temp->code, temp->name, temp->price, temp->count, temp->category);
        temp = temp->next;
    }
}

ITEM* search_item(ITEM *it, char name[]) {

    ITEM *tmp = it->next;
    int check = 0;

    while(tmp == NULL) {
        printf("상품이 존재하지 않음.\n");
        return NULL;
    }

    while(tmp != NULL) {
        if(strcmp(tmp->name, name) == 0) {
            return tmp;
            break;
        }
        tmp = tmp->next;  
    }
    
    return NULL;
}

void load_member_file(MEMBER *member, FILE *fp) {
    MEMBER *tmp;
    MEMBER *last;

    tmp = (MEMBER *) malloc(sizeof(MEMBER));

    fscanf(fp, "%s %s %s %s %s", tmp->id, tmp->pw, tmp->name, tmp->phone, tmp->role);
    if(feof(fp) == 0) {

        member->next = tmp;
        last = tmp;
    }
    else {
        free(tmp);
    }

    tmp = (MEMBER *) malloc(sizeof(MEMBER));

    fscanf(fp, "%s %s %s %s %s", tmp->id, tmp->pw, tmp->name, tmp->phone, tmp->role);
    if(feof(fp) == 0) {

        last->next = tmp;
        last = tmp;
    }
    else {
        free(tmp);
    }

    while(1) {
        tmp = (MEMBER *) malloc(sizeof(MEMBER));

        fscanf(fp, "%s %s %s %s %s", tmp->id, tmp->pw, tmp->name, tmp->phone, tmp->role);
        if(feof(fp) == 0) {

            last->next = tmp;
            last = tmp;
        }
        else {
            free(tmp);
            break;
        }
    }
}


void add_member(FILE *fp, MEMBER *member) {

    fp = fopen("employee.txt", "a+");
    if(fp == NULL) {
        printf("파일열기 실패.\n");
        exit(1);
    }

    MEMBER* member2 = (MEMBER*)malloc(sizeof(MEMBER));
    init_member(member2);

    MEMBER* temp = member;
    while(temp->next != NULL) {
        temp = temp->next;
    }

    getchar();
    printf("아이디 : ");
    scanf("%s", member2->id);
    printf("패스워드 : ");
    scanf("%s", member2->pw);
    printf("이름 : ");
    scanf("%s", member2->name);
    printf("전화번호 : ");
    scanf("%s", member2->phone);
    printf("권한 : ");
    scanf("%s", member2->role);

    temp->next = member2;

    fprintf(fp, "%s\t\t%s\t\t%s\t\t%s\t\t%s\n", member2->id, member2->pw, member2->name, member2->phone, member2->role);

    fclose(fp);
}

void update_member(MEMBER *member) {
    char id[20];
    printf("수정할 직원 아이디 입력 : ");
    getchar();
    scanf("%s", id);

    MEMBER* temp = member->next;
    FILE* fpw = fopen("employee_tmp.txt", "w");

    if(fpw == NULL) {
        printf("파일 열기 실패\n");
        exit(1);
    }

    int check_count = 0;

    while(temp != NULL) {
        if(strcmp(temp->id, id) == 0) {
            check_count++;
            int select = 0;

            printf("1. 아이디\n");
            printf("2. 패스워드\n");
            printf("3. 이름\n");
            printf("4. 핸드폰\n");
            printf("5. 권한\n");
            printf("선택하세요 (선택지 이외 숫자 입력시 취소) >> ");
            scanf("%d", &select);

        
            switch(select){
                case 1: 
                    printf("수정될 아이디 : ");
                    getchar();
                    scanf("%s", temp->id);
                    break;
                case 2:
                    printf("수정될 패스워드 : ");
                    getchar();
                    scanf("%s", temp->pw);
                    break;
                case 3:
                    printf("수정될 이름 : ");
                    getchar();
                    scanf("%s", temp->name);
                    break;
                case 4:
                    printf("수정될 전화번호 : ");
                    getchar();
                    scanf("%s", temp->phone);
                    break;
                case 5:
                    printf("수정될 권한 : ");
                    getchar();
                    scanf("%s", temp->role);
                    break;

                default:
                    printf("종료합니다.\n");
                    break;
            }
        }
        fprintf(fpw, "%s\t\t%s\t\t%s\t\t%s\t\t%s\n", temp->id, temp->pw, temp->name, temp->phone, temp->role);
        
        temp = temp->next;
        
    }
    fclose(fpw);

    if(check_count == 0) {  
        remove("employee_tmp.txt");
    }

    else {
        remove("employee.txt");
        rename("employee_tmp.txt", "employee.txt");
    }
}

void delete_member(MEMBER *member) {
    char id[10];
    printf("삭제할 직원 id : ");
    getchar();
    scanf("%s", id);

    if(member == NULL) {
        printf("존재하지 않는 직원입니다.\n");
        return;
    }

    FILE* fpw = fopen("employee_tmp.txt", "w");

    if(fpw == NULL) {
        printf("파일 열기 실패\n");
        exit(1);
    }

    MEMBER *cur = member;
    MEMBER *prev = NULL;

    while(cur != NULL) {
        if(strcmp(cur->id, id) == 0) {
            if(prev == NULL) {
                member->next = cur->next;
            }
            else {
                prev->next = cur->next;
            }
            free(cur);
        }

        else {
            fprintf(fpw, "%s\t\t%s\t\t%s\t\t%s\t\t%s\n", cur->id, cur->pw, cur->name, cur->phone, cur->role);
        }

        prev = cur;
        cur = cur->next;
    }
    fclose(fpw);
    
    remove("employee.txt");
    rename("employee_tmp.txt", "employee.txt");
}

void read_member(MEMBER *member) {
    MEMBER* temp = member->next;
    printf("아이디\t\t패스워드\t이름\t\t전화번호\t\t권한\n");
    while(temp != NULL) {
        printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\n", temp->id, temp->pw, temp->name, temp->phone, temp->role);
        temp = temp->next;
    }
}

int search_member(MEMBER *member, char id[], char pw[]) {
    MEMBER *tmp = member->next;
    int check = 0;

    while(tmp == NULL) {
        printf("존재하지 않는 회원입니다.\n");
        return 3;
    }

    while(tmp != NULL) {
        if(strcmp(tmp->id, id) == 0 && strcmp(tmp->pw, pw) == 0) {
            if(strcmp(tmp->role, "manager") == 0) {
                check = 1;
                break;
            }
            else if(strcmp(tmp->role, "staff") == 0) {
                check = 2;
                break;
            }
        }
        else {
            tmp = tmp->next;
            check = 0;
        }
    }
    
    return check;
}

void load_sales_file(SALES *sales, FILE *fp) {
    SALES *tmp;
    SALES *last;

    tmp = (SALES *) malloc(sizeof(SALES));

    fscanf(fp, "%s %s %s %s", tmp->name, tmp->product_price, tmp->sales_count, tmp->sales_price);
    if(feof(fp) == 0) {

        sales->next = tmp;
        last = tmp;
    }
    else {
        free(tmp);
    }

    tmp = (SALES *) malloc(sizeof(SALES));
    fscanf(fp, "%s %s %s %s", tmp->name, tmp->product_price, tmp->sales_count, tmp->sales_price);
    if(feof(fp) == 0) {

        last->next = tmp;
        last = tmp;
    }
    else {
        free(tmp);
    }

    while(1) {
        tmp = (SALES *) malloc(sizeof(SALES));

        fscanf(fp, "%s %s %s %s", tmp->name, tmp->product_price, tmp->sales_count, tmp->sales_price);
        if(feof(fp) == 0) {

            last->next = tmp;
            last = tmp;
        }
        else {
            free(tmp);
            break;
        }
    }
}

void add_sales(FILE *fp, SALES *sales, ITEM *item) {
    ITEM* search = (ITEM*) malloc(sizeof(ITEM));
    
    init_item(search);

    char name[20];
    char sales_count[10];

    printf("검색할 상품 이름 : ");
    getchar();
    scanf("%s", name);

    search = search_item(item, name);

    int price = 0;
    int count = 0;
    int total_price = 0;

    fp = fopen("sales.txt", "a+");
    if(fp == NULL) {
        printf("파일열기 실패.\n");
        exit(1);
    }

    SALES *tmp = (SALES *) malloc(sizeof(SALES));
    init_sales(tmp);
    
    SALES *tmp2 = sales;
    while(tmp2->next != NULL) {
        tmp2 = tmp2->next;
    }

    if(search != NULL) {
        strcpy(tmp2->name, search->name);
        strcpy(tmp2->product_price, search->price);
        printf("판매 수량 : ");
        scanf("%s", sales_count);
        strcpy(tmp2->sales_count, sales_count);

        price = atoi(search->price);
        count = atoi(sales_count);

        total_price = price * count;

        sprintf(tmp2->sales_price, "%d", total_price);

        tmp->next = tmp2;

        fprintf(fp, "%s\t\t%s\t\t%s\t\t%s\n", tmp2->name, tmp2->product_price, tmp2->sales_count, tmp2->sales_price);

        printf("<<상품 판매 완료>>\n");

        fclose(fp);
    }
    
}

void update_sales(SALES *sales) {
    
}


void remove_sale(SALES *sales) {
    
}

void read_sales(SALES *sales) {
    SALES* temp = sales->next;
    printf("상품 이름\t판매가\t\t판매 수량\t누적 판매액\n");
    while(temp != NULL) {
        printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\n", temp->name, temp->product_price, temp->sales_count, temp->sales_price);
        temp = temp->next;
    }
}

int login() {
    int result = 0;
    /*멤버 구조체 초기화*/
    MEMBER *member = (MEMBER *) malloc(sizeof(MEMBER));
    init_member(member);

    /*멤버 파일 열기*/
    FILE *fp; 
    fp = fopen("employee.txt", "r");

    if(fp != NULL) {
        load_member_file(member, fp);
        fclose(fp);
    }

    while(member->next == NULL) {
        add_member(fp, member);
    }

    while(1) {
        print_index();

        int select = 0;
        int check = 0;
        char id[10];
        char pw[10];

        scanf("%d", &select);
        printf("\n\n");

        if(select == 0) {
            exit(0);
        }

        switch(select) {
                case 1:
                printf("id : ");
                scanf("%s", id);
                printf("pw : ");
                scanf("%s", pw);
                check = search_member(member, id, pw);
                if(check == 1)  {
                    system("cls");
                    result = 1;
                    return result;
                }
                else if(check == 2) {
                    system("cls");
                    result = 2;
                    return result;
                }
                else{
                    printf("아이디 또는 비밀번호가 잘못되었습니다.\n");
                    system("cls");
                    break;
                }
                
            default:
                printf("잘못 입력하셨습니다.\n");
                system("cls");
                break;
            
        }
    
    }

    {
        MEMBER *temp = member;
        MEMBER *temp2;

        while(temp != NULL) {
            temp2 = temp->next;
            free(temp);
            temp = temp2;
        }
    }

    return result;
}

void print_manager_menu() {
    printf("매니저 모드로 로그인 합니다.\n\n\n");

    printf("=================================================\n");
    printf("|================ STORE MANAGER ================|\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                  1. 재고 관리                 |\n");
    printf("|                  2. 직원 관리                 |\n");
    printf("|                  3. 판매/반품                 |\n");
    printf("|                  4. 매출 관리                 |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|===============================================|\n");
    printf("=================================================\n");
    printf(">> ('0' 입력시 종료) ");

}

void print_staff_menu() {
    printf("스태프 모드로 로그인 합니다.\n\n\n");

    printf("=================================================\n");
    printf("|================ STORE MANAGER ================|\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                  1. 판매/반품                 |\n");
    printf("|                  2. 매출 내역                 |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|===============================================|\n");
    printf("=================================================\n");
    printf(">> ('0' 입력시 종료) ");
}

void print_inventory_menu() {
    printf("=================================================\n");
    printf("|================ STORE MANAGER ================|\n");
    printf("|                 | 재고 관리 |                 |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                  1. 재고 등록                 |\n");
    printf("|                  2. 재고 조회                 |\n");
    printf("|                  3. 재고 수정                 |\n");
    printf("|                  4. 재고 삭제                 |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|===============================================|\n");
    printf("=================================================\n");
    printf(">> ('0' 입력시 종료) ");
}

void print_employee_menu() {
    printf("=================================================\n");
    printf("|================ STORE MANAGER ================|\n");
    printf("|                 | 직원 관리 |                 |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                  1. 직원 등록                 |\n");
    printf("|                  2. 직원 조회                 |\n");
    printf("|                  3. 직원 수정                 |\n");
    printf("|                  4. 직원 삭제                 |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|===============================================|\n");
    printf("=================================================\n");
    printf(">> ('0' 입력시 종료) ");

}

void print_sale_menu() {
    printf("=================================================\n");
    printf("|================ STORE MANAGER ================|\n");
    printf("|                 | 판매/반품 |                 |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                  1. 상품 판매                 |\n");
    printf("|                  2. 상품 반품                 |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|===============================================|\n");
    printf("=================================================\n");
    printf(">> ('0' 입력시 종료) ");

}

void print_sales_menu() {
    printf("=================================================\n");
}

void inventory_menu() {

    ITEM *item = (ITEM *)malloc(sizeof(ITEM));
    init_item(item);

    FILE *fp; 
    fp = fopen("inventory.txt", "r");

    if(fp != NULL) {
        load_item_file(item, fp);
        fclose(fp);
    }

     while(1) {
        int select = 0;
        print_inventory_menu();
        scanf("%d", &select);
        printf("\n\n");

        if(select == 0) {
            system("cls");
            manager_menu_handler();
            return;
        }

        switch(select) {
            case 1:
                system("cls");
                add_item(fp, item);
                break;

            case 2:
                printf("\n\n======== 조회할 상품 목록 ========\n\n");
                read_item(item);
                break;
                
            case 3:
                system("cls"); 
                update_item(item);
                break;
        
            case 4:
                system("cls");
                delete_item(item);
                break;

            default:
                system("cls");
                sleep(2);
                printf("잘못된 입력입니다.\n");
                break;
        }

    }

    {
        ITEM *temp = item;
        ITEM *temp2;

        while(temp != NULL) {
            temp2 = temp->next;
            free(temp);
            temp = temp2;
        }
    }

}


void employee_menu() {

    MEMBER *member = (MEMBER *)malloc(sizeof(MEMBER));
    init_member(member);

    FILE *fp; 
    fp = fopen("employee.txt", "r");

    if(fp != NULL) {
        load_member_file(member, fp);
        fclose(fp);
    }

     while(1) {
        int select = 0;
        print_employee_menu();
        scanf("%d", &select);
        printf("\n\n");

        if(select == 0) {
            system("cls");
            manager_menu_handler();
            return;
        }

        switch(select) {
            case 1:
                system("cls");
                add_member(fp, member);
                break;

            case 2:
                printf("\n\n======== 조회할 직원 목록 ========\n\n");
                read_member(member);
                break;
                
            case 3: 
                system("cls");
                update_member(member);
                break;
        
            case 4:
                system("cls");
                delete_member(member);
                break;

            default:
                system("cls");
                sleep(2);
                printf("잘못된 입력입니다.\n");
                break;
        }

    }

    {
        MEMBER *temp = member;
        MEMBER *temp2;

        while(temp != NULL) {
            temp2 = temp->next;
            free(temp);
            temp = temp2;
        }
    }

}

void sale_menu() {
    SALES *sales = (SALES *)malloc(sizeof(SALES));
    init_sales(sales);

    FILE *fp; 
    fp = fopen("sales.txt", "r");

    if(fp != NULL) {
        load_sales_file(sales, fp);
        fclose(fp);
    }

    ITEM *item = (ITEM *)malloc(sizeof(ITEM));
    init_item(item);

    FILE *fp2; 
    fp2 = fopen("inventory.txt", "r");

    if(fp2 != NULL) {
        load_item_file(item, fp2);
        fclose(fp);
    }

     while(1) {
        int select = 0;
        print_sale_menu();
        scanf("%d", &select);
        printf("\n\n");

        if(select == 0) {
            system("cls");
            manager_menu_handler();
            return;
        }

        switch(select) {
            case 1:
                system("cls");
                
                add_sales(fp, sales, item);
                break;

            case 2:
                system("cls");
                update_sales(sales);
                break;
        
            default:
                system("cls");
                sleep(2);
                printf("잘못된 입력입니다.\n");
                break;
        }

    }

    {
        SALES *temp = sales;
        SALES *temp2;

        while(temp != NULL) {
            temp2 = temp->next;
            free(temp);
            temp = temp2;
        }
    }
}

void sales_menu() {
    SALES *sales = (SALES *)malloc(sizeof(SALES));
    init_sales(sales);

    FILE *fp; 
    fp = fopen("sales.txt", "r");

    if(fp != NULL) {
        load_sales_file(sales, fp);
        fclose(fp);
    }
    while(1) {
        int select = 0;

        read_sales(sales);

        printf("\n\n0. 메인 메뉴로 돌아가기\n");
        scanf("%d", &select);

        if(select == 0) {
            system("cls");
            manager_menu_handler();
            return;
        }

        
    }
    

    {
        SALES *temp = sales;
        SALES *temp2;

        while(temp != NULL) {
            temp2 = temp->next;
            free(temp);
            temp = temp2;
        }
    }

}


int manager_menu_handler() {

    while(1) {
        int select = 0;
        int result = 0;
        print_manager_menu();

        scanf("%d", &select);
        printf("\n\n");

        if(select == 0) {
            exit(0);
        }

        switch(select) {
            case 1:
                result = 1;
                return result;
            case 2:
                result = 2;
                return result;
            case 3:
                result = 3;
                return result;
            case 4:
                result = 4;
                return result;
            default:
                printf("잘못 입력하셨습니다.\n");
                break;
        }
    }
    return 0;

}

int staff_menu_handler() {

    while(1) {
        int result = 0;
        int select = 0;
        print_staff_menu();

        scanf("%d", &select);
        printf("\n\n");

        if(select == 0) {
            exit(0);
        }

        switch(select) {
            case 1:
                result = 1;
                return result;
            case 2:
                result = 2;
                return result;
            
            default:
                printf("잘못 입력하셨습니다.\n");
                break;
        }
    }

    return 0;
}

int main(void) {
    int start = 0;
    int manager = 0;
    int staff = 0;
    start = login();
    
    if(start == 1) {
        manager = manager_menu_handler();
        if(manager == 1) {
            system("cls");
            inventory_menu();
        } else if(manager == 2) {
            system("cls");
            employee_menu();
        } else if(manager == 3) {
            system("cls");
            sale_menu();
        } else if(manager == 4) {
            system("cls");
            sales_menu();
        }
    }
    else if(start == 2) {
        staff = staff_menu_handler();
        if(staff == 1) {
            system("cls");
            sale_menu();
        }
        else if(staff == 2) {
            system("cls");
            sales_menu();
        }
    }
    return 0;
}


