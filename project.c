#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

// ==============================
// 1. KHAI BÁO CẤU TRÚC
// ==============================
typedef struct
{
    char cardId[10];
    char name[50];
    char phone[15];
    double debt;
    int visitDays;
} Patient;

typedef struct
{
    char recId[20];
    char cardId[10];
    char date[11];
    char status[20];
    double cost;
} Record;

// ==============================
// 2. MẢNG LƯU DỮ LIỆU
// ==============================
Patient patients[MAX];
Record records[MAX];
int pCount = 0; // số bệnh nhân
int rCount = 0; // số record

// ==============================
// 3. KHỞI TẠO DỮ LIỆU MẪU
// ==============================
void initializeData()
{
    // -------------------------
    // Bệnh nhân 1
    // -------------------------
    strcpy(patients[pCount].cardId, "BN001");
    strcpy(patients[pCount].name, "Nguyen Van An");
    strcpy(patients[pCount].phone, "0901234567");
    patients[pCount].debt = 150000.0;
    patients[pCount].visitDays = 2;
    pCount++;

    // -------------------------
    // Bệnh nhân 2
    // -------------------------
    strcpy(patients[pCount].cardId, "BN002");
    strcpy(patients[pCount].name, "Tran Thi Binh");
    strcpy(patients[pCount].phone, "0918765432");
    patients[pCount].debt = 500000.0;
    patients[pCount].visitDays = 1;
    pCount++;

    // -------------------------
    // Bệnh nhân 3
    // -------------------------
    strcpy(patients[pCount].cardId, "BN003");
    strcpy(patients[pCount].name, "Le Van Linh");
    strcpy(patients[pCount].phone, "0975556660");
    patients[pCount].debt = 90.0;
    patients[pCount].visitDays = 0;
    pCount++;

    // -------------------------
    // Bệnh nhân 4
    // -------------------------
    strcpy(patients[pCount].cardId, "BN004");
    strcpy(patients[pCount].name, "Pham Minh Quan");
    strcpy(patients[pCount].phone, "0868889991");
    patients[pCount].debt = 320000.0;
    patients[pCount].visitDays = 3;
    pCount++;

    // -------------------------
    // Bệnh nhân 5
    // -------------------------
    strcpy(patients[pCount].cardId, "BN005");
    strcpy(patients[pCount].name, "Hoang Ngoc Son");
    strcpy(patients[pCount].phone, "0383332224");
    patients[pCount].debt = 80000.0;
    patients[pCount].visitDays = 1;
    pCount++;

    // -------------------------
    // Thêm 2 record mẫu
    // -------------------------
    // Record cho BN001
    strcpy(records[rCount].recId, "REC001");
    strcpy(records[rCount].cardId, "BN001");
    strcpy(records[rCount].date, "2025/11/20");
    strcpy(records[rCount].status, "Cam cum");
    records[rCount].cost = 50000.0;
    rCount++;

    // Record cho BN002
    strcpy(records[rCount].recId, "REC002");
    strcpy(records[rCount].cardId, "BN002");
    strcpy(records[rCount].date, "2025/11/27");
    strcpy(records[rCount].status, "Dau da day");
    records[rCount].cost = 500000.0;
    rCount++;
}

void printfMenu(void)
{
    printf("\n+---------------------------+\n");
    printf("|         MENU CHINH        |\n");
    printf("+---------------------------+\n");
    printf("| 1. Tiep nhan benh nhan    |\n");
    printf("| 2. Cap nhat benh nhan     |\n");
    printf("| 3. Xuat vien              |\n");
    printf("| 4. Hien thi danh sach     |\n");
    printf("| 5. Tim kiem theo ten      |\n");
    printf("| 6. Sap xep theo cong no   |\n");
    printf("| 7. Ghi nhan kham benh     |\n");
    printf("| 8. Xem lich su kham benh  |\n");
    printf("| 9. Thoat                  |\n");
    printf("+---------------------------+\n");
}

// f01 tiep nhan benh nhan
// ==============================
// F01 – TIẾP NHẬN BỆNH NHÂN (Đã thêm Validation: debt >= 0)
// ==============================
void addPatient() // f01 tiep nhan benh nhan
{
    if (pCount >= MAX)
    {
        printf("Danh sach benh nhan da day!\n");
        return;
    }
    int isDuplicate = 0;
    while (1)
    {
        printf("Nhap ma benh nhan: ");
        fgets(patients[pCount].cardId, 10, stdin);
        patients[pCount].cardId[strcspn(patients[pCount].cardId, "\n")] = '\0';

        if (strlen(patients[pCount].cardId) == 0)
        {
            printf("ban chua nhap ID!\n");
            continue;
        }

        isDuplicate = 0;
        for (int i = 0; i < pCount; i++)
        {
            if (strcmp(patients[i].cardId, patients[pCount].cardId) == 0)
            {
                printf("Ma benh nhan bi trung! Vui long nhap ma khac.\n");
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate)
            break;
    }

    // Nhap ten benh nhan (khong de trong)
    while (1)
    {
        printf("Nhap ten benh nhan: ");
        fgets(patients[pCount].name, sizeof(patients[pCount].name), stdin);
        patients[pCount].name[strcspn(patients[pCount].name, "\n")] = '\0';
        if (strlen(patients[pCount].name) == 0)
        {
            printf("khong duoc de trong!\n");
            continue;
        }
        break;
    }

    // Nhap so dien thoai va kiem tra hop le
    while (1)
    {
        printf("Nhap so dien thoai: ");
        fgets(patients[pCount].phone, sizeof(patients[pCount].phone), stdin);
        patients[pCount].phone[strcspn(patients[pCount].phone, "\n")] = '\0';
        if (strlen(patients[pCount].phone) == 0)
        {
            printf("khong duoc de trong!\n");
            continue;
        }
        else if (strlen(patients[pCount].phone) < 9 || strlen(patients[pCount].phone) > 15)
        {
            printf("so vua nhap khong dung dinh dang (9-15 chu so).\n");
            continue;
        }
        int available = 1;
        for (int i = 0; patients[pCount].phone[i] != '\0'; i++)
        {
            if (patients[pCount].phone[i] < '0' || patients[pCount].phone[i] > '9')
            {
                available = 0;
                break;
            }
        }
        if (!available)
        {
            printf("so dien thoai chi chua so!\n");
            continue;
        }
        // valid phone
        break;
    }

    printf("Nhap cong no ban dau (>= 0): ");
    // Đã thay đổi điều kiện vòng lặp: kiểm tra cả tính hợp lệ của số và giá trị >= 0
    while (scanf("%lf", &patients[pCount].debt) != 1 || patients[pCount].debt < 0)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Gia tri khong hop le (phai la so >= 0). Nhap lai cong no ban dau: ");
    }
    getchar();

    patients[pCount].visitDays = 0; // mac dinh = 0

    pCount++;
    printf("Da them benh nhan moi!\n");
}

// ==============================
// F02 – CẬP NHẬT BỆNH NHÂN
// ==============================
void updatePatient()
{
    char id[10];
    printf("Nhap ma benh nhan can cap nhat: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int pos = -1;
    for (int i = 0; i < pCount; i++)
    {
        if (strcmp(patients[i].cardId, id) == 0)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        printf("Khong tim thay benh nhan!\n");
        return;
    }

    printf("Thong tin benh nhan can thay doi:\n");
    printf("╔════════════╦══════════════════════════╦══════════════════╦═══════════╦═════════════╗\n");
    printf("║    Ma BN   ║          Ho Ten          ║        SDT       ║    No     ║ So lan kham ║\n");
    printf("╠════════════╬══════════════════════════╬══════════════════╬═══════════╬═════════════╣\n");

    printf("║ %-9s  ║ %-24s ║ %-16s ║ %-9.2lf ║ %-11d ║\n",
           patients[pos].cardId,
           patients[pos].name,
           patients[pos].phone,
           patients[pos].debt,
           patients[pos].visitDays);

    printf("╚════════════╩══════════════════════════╩══════════════════╩═══════════╩═════════════╝\n");

    printf("Nhap ten moi: ");
    fgets(patients[pos].name, sizeof(patients[pos].name), stdin);
    patients[pos].name[strcspn(patients[pos].name, "\n")] = '\0';

    printf("Nhap SDT moi: ");
    fgets(patients[pos].phone, sizeof(patients[pos].phone), stdin);
    patients[pos].phone[strcspn(patients[pos].phone, "\n")] = '\0';

    printf("Nhap cong no moi: ");
    while (scanf("%lf", &patients[pos].debt) != 1 || patients[pos].debt < 0)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Gia tri khong hop le (phai la so >= 0). Nhap lai cong no: ");
    }
    getchar();

    printf("Cap nhat thanh cong!\n");
}

// ==============================
// F03 – XUẤT VIỆN (XÓA BỆNH NHÂN)
// ==============================
void deletePatient()
{
    char id[10];
    printf("Nhap ma benh nhan muon xuat vien: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int pos = -1;
    for (int i = 0; i < pCount; i++)
    {
        if (strcmp(patients[i].cardId, id) == 0)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        printf("Khong tim thay benh nhan!\n");
        return;
    }

    printf("Thong tin benh nhan can xuat vien:\n");
    printf("╔════════════╦══════════════════════════╦══════════════════╦═══════════╦═════════════╗\n");
    printf("║    Ma BN   ║          Ho Ten          ║        SDT       ║    No     ║ So lan kham ║\n");
    printf("╠════════════╬══════════════════════════╬══════════════════╬═══════════╬═════════════╣\n");

    printf("║ %-9s  ║ %-24s ║ %-16s ║ %-9.2lf ║ %-11d ║\n",
           patients[pos].cardId,
           patients[pos].name,
           patients[pos].phone,
           patients[pos].debt,
           patients[pos].visitDays);

    printf("╚════════════╩══════════════════════════╩══════════════════╩═══════════╩═════════════╝\n");

    if (patients[pos].debt > 0)
    {
        printf("CANH BAO: Benh nhan van con no %.2lf\n", patients[pos].debt);
    }

    printf("Ban co muon thanh toan cong no (neu co) va xuat vien khong?(yes-1/no-0): ");
    int temp;
    if (scanf("%d", &temp) != 1)
    {
        // Xử lý nhập không hợp lệ
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Loi nhap. Benh nhan khong duoc xuat vien!\n");
        return;
    }
    getchar(); // Clear buffer

    if (temp == 1)
    {
        // Xoá bệnh nhân
        for (int i = pos; i < pCount - 1; i++)
        {
            patients[i] = patients[i + 1];
        }
        pCount--;

        printf("Da xuat vien thanh cong!\n");
    }
    else
    {
        printf("Benh nhan khong the xuat vien hoac ban da chon khong thanh toan!\n");
    }
}

// ==============================
// F04 – HIỂN THỊ DANH SÁCH
// ==============================
void showPatients()
{
    if (pCount == 0)
    {
        printf("Khong co benh nhan nao!\n");
        return;
    }

    const int pageSize = 5;
    int totalPages = (pCount + pageSize - 1) / pageSize;
    int currentPage = 1;

    do
    {
        int startIndex = (currentPage - 1) * pageSize;
        int endIndex = startIndex + pageSize;
        if (endIndex > pCount)
        {
            endIndex = pCount;
        }

        printf("\n DANH SACH BENH NHAN (Trang %d/%d) \n", currentPage, totalPages);
        printf("╔════╦═══════════╦══════════════════════════╦══════════════════╦═══════════╦═════════════╗\n");
        printf("║ STT║   Ma BN   ║          Ho Ten          ║        SDT       ║    No     ║ So lan kham ║\n");
        printf("╠════╬═══════════╬══════════════════════════╬══════════════════╬═══════════╬═════════════╣\n");

        for (int i = startIndex; i < endIndex; i++)
        {
            printf("║ %-2d ║ %-9s ║ %-24s ║ %-16s ║ %-9.2lf ║ %-11d ║\n",
                   i + 1,
                   patients[i].cardId,
                   patients[i].name,
                   patients[i].phone,
                   patients[i].debt,
                   patients[i].visitDays);
        }

        printf("╚════╩═══════════╩══════════════════════════╩══════════════════╩═══════════╩═════════════╝\n");

        if (totalPages > 1)
        {
            printf("\n--- Trang hien tai: %d/%d ---\n", currentPage, totalPages);
            printf("Nhap so trang muon xem (1 - %d), hoac 0 de thoat: ", totalPages);

            int nextChoice;
            if (scanf("%d", &nextChoice) != 1)
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                {
                }
                printf("Loi nhap. Vui long nhap lai.\n");
                continue;
            }
            getchar(); // Clear buffer

            if (nextChoice == 0)
            {
                break; // Thoát khỏi vòng lặp phân trang
            }
            else if (nextChoice >= 1 && nextChoice <= totalPages)
            {
                currentPage = nextChoice;
            }
            else
            {
                printf("So trang khong hop le.\n");
            }
        }
        else
        {
            // Chỉ có 1 trang
            break;
        }

    } while (1);
}
// ==============================
// F05 – TÌM KIẾM THEO TÊN
// ==============================
void searchPatient()
{
    char key[50];
    printf("Nhap ten (hoac mot phan ten): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    int found = 0;

    printf("\nKET QUA TIM KIEM\n");
    printf("╔════╦═══════════╦══════════════════════════╦══════════════════╦═══════════╦═════════════╗\n");
    printf("║ STT║   Ma BN   ║          Ho Ten          ║        SDT       ║    No     ║ So lan kham ║\n");
    printf("╠════╬═══════════╬══════════════════════════╬══════════════════╬═══════════╬═════════════╣\n");

    for (int i = 0; i < pCount; i++)
    {
        if (strstr(patients[i].name, key) != NULL)
        { // tìm chuỗi con
            printf("║ %-2d ║ %-9s ║ %-24s ║ %-16s ║ %-9.2lf ║ %-11d ║\n",
                   i + 1,
                   patients[i].cardId,
                   patients[i].name,
                   patients[i].phone,
                   patients[i].debt,
                   patients[i].visitDays);
            found = 1;
        }
    }

    printf("╚════╩═══════════╩══════════════════════════╩══════════════════╩═══════════╩═════════════╝\n");

    if (!found)
        printf("Khong tim thay benh nhan!\n");
}

// ==============================
// F06 – SẮP XẾP THEO NỢ (TĂNG DẦN)
// ==============================
void sortDebt()
{
    for (int i = 0; i < pCount - 1; i++)
    {
        for (int j = i + 1; j < pCount; j++)
        {
            if (patients[i].debt > patients[j].debt)
            {
                Patient temp = patients[i];
                patients[i] = patients[j];
                patients[j] = temp;
            }
        }
    }
    printf("Da sap xep theo cong no (tang dan)!\n");

    const int pageSize = 5;
    int totalPages = (pCount + pageSize - 1) / pageSize;
    int currentPage = 1;

    do
    {
        int startIndex = (currentPage - 1) * pageSize;
        int endIndex = startIndex + pageSize;
        if (endIndex > pCount)
        {
            endIndex = pCount;
        }

        printf("╔════╦═══════════╦══════════════════════════╦══════════════════╦═══════════╦═════════════╗\n");
        printf("║ STT║   Ma BN   ║          Ho Ten          ║        SDT       ║    No     ║ So lan kham ║\n");
        printf("╠════╬═══════════╬══════════════════════════╬══════════════════╬═══════════╬═════════════╣\n");

        for (int i = startIndex; i < endIndex; i++)
        {
            printf("║ %-2d ║ %-9s ║ %-24s ║ %-16s ║ %-9.2lf ║ %-11d ║\n",
                   i + 1,
                   patients[i].cardId,
                   patients[i].name,
                   patients[i].phone,
                   patients[i].debt,
                   patients[i].visitDays);
        }

        printf("╚════╩═══════════╩══════════════════════════╩══════════════════╩═══════════╩═════════════╝\n");

        if (totalPages > 1)
        {
            printf("\n--- Trang hien tai: %d/%d ---\n", currentPage, totalPages);
            printf("Nhap so trang muon xem (1 - %d), hoac 0 de thoat: ", totalPages);

            int nextChoice;
            if (scanf("%d", &nextChoice) != 1)
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                {
                }
                printf("Loi nhap. Vui long nhap lai.\n");
                continue;
            }
            getchar(); // Clear buffer

            if (nextChoice == 0)
            {
                break; // Thoát khỏi vòng lặp phân trang
            }
            else if (nextChoice >= 1 && nextChoice <= totalPages)
            {
                currentPage = nextChoice;
            }
            else
            {
                printf("So trang khong hop le.\n");
            }
        }
        else
        {
            // Chỉ có 1 trang
            break;
        }

    } while (1);
}

// ==============================
// F07 – GHI NHẬN KHÁM BỆNH
// ==============================
void addRecord()
{
    if (rCount >= MAX)
    {
        printf("Danh sach record da day!\n");
        return;
    }
    char id[10];
    printf("Nhap ma benh nhan: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int pos = -1;
    for (int i = 0; i < pCount; i++)
    {
        if (strcmp(patients[i].cardId, id) == 0)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        printf("Khong tim thay benh nhan!\n");
        return;
    }

    printf("Nhap ma lan kham: ");
    fgets(records[rCount].recId, sizeof(records[rCount].recId), stdin);
    records[rCount].recId[strcspn(records[rCount].recId, "\n")] = '\0';

    strcpy(records[rCount].cardId, id);

    do
    {
        printf("Nhap ngay kham(dd/mm/yyyy): ");
        fgets(records[rCount].date, sizeof(records[rCount].date), stdin);
        records[rCount].date[strcspn(records[rCount].date, "\n")] = '\0';
        int day, month, year;
        getchar();
        if (sscanf(records[rCount].date, "%d/%d/%d", &day, &month, &year) != 3)
        {
            printf("Ngay kham bi sai!\n");
            continue;
        }
        if (day < 1 || day > 31 || month < 1 || month > 12)
        {
            printf("Ngay kham bi sai!\n");
            continue;
        }
        break;
    } while (1);

    printf("Nhap trang thai: ");
    fgets(records[rCount].status, sizeof(records[rCount].status), stdin);
    records[rCount].status[strcspn(records[rCount].status, "\n")] = '\0';

    printf("Nhap chi phi: ");
    while (scanf("%lf", &records[rCount].cost) != 1 || records[rCount].cost < 0)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Gia tri khong hop le (phai la so >= 0). Nhap lai cong no ban dau: ");
    }
    getchar();

    patients[pos].visitDays++;
    patients[pos].debt += records[rCount].cost;

    rCount++;
    printf("Da ghi nhan kham benh!\n");
}

// ==============================
// F08 – XEM LỊCH SỬ KHÁM
// ==============================
void showHistory()
{
    char id[10];
    printf("Nhap ma benh nhan: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';
    int found = 1;
    printf("\nLICH SU KHAM BENH CUA BENH NHAN: %s \n", id);
    printf("╔════════╦════════════╦══════════════════════════╦══════════════════╗\n");
    printf("║ Rec ID ║   Status   ║         Ngay kham        ║     Chi phi      ║\n");
    printf("╠════════╬════════════╬══════════════════════════╬══════════════════╣\n");

    for (int i = 0; i < rCount; i++)
    {
        if (strcmp(records[i].cardId, id) == 0)
        {
            printf("║ %-6s ║ %-10s ║ %-24s ║ %-16.2lf ║\n",
                   records[i].recId,
                   records[i].status,
                   records[i].date,
                   records[i].cost);
            found = 1;
        }
    }
    printf("╚════════╩════════════╩══════════════════════════╩══════════════════╝\n");

    if (!found)
        printf("Khong co lich su kham cho ma benh nhan nay!\n");
}

// ==============================
// F09 – THOÁT CHƯƠNG TRÌNH
// ==============================
void exitProgram()
{
    pCount = 0;
    rCount = 0;
    printf("Du lieu trong RAM da duoc reset.\n");
    printf("Thoat chuong trinh...\n");
}

// ==============================
// MAIN
// ==============================
int main(void)
{
#ifdef _WIN32
    system("chcp 65001");
#endif

    initializeData();
    printf("Da khoi tao %d benh nhan mau.\n", pCount);

    int choice = 0;
    do
    {
        printfMenu();
        do
        {
            printf("Chon chuc nang (1-9): ");
            if (scanf("%d", &choice) != 1)
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                {
                }
                printf("Lua chon khong hop le! Vui long nhap so tu 1 den 9.\n");
                choice = -1;
                continue;
            }
            getchar();
            if (choice < 1 || choice > 9)
            {
                printf("Lua chon khong hop le!\n");
                continue;
            }
            else
                break;
        } while (1);

        switch (choice)
        {
        case 1:
            addPatient();
            break;
        case 2:
            updatePatient();
            break;
        case 3:
            deletePatient();
            break;
        case 4:
            showPatients();
            break;
        case 5:
            searchPatient();
            break;
        case 6:
            sortDebt();
            break;
        case 7:
            addRecord();
            break;
        case 8:
            showHistory();
            break;
        case 9:
            exitProgram();
            return 0;
        default:
            printf("Lua chon khong hop le!\n");
        }
    } while (1);

    return 0;
}
