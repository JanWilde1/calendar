#include <iostream>
#include <string>

int day_of_week(int year, int month, int day);
void display_calendar(int dow, int year, int month);

int days_in_month[] = {
    31, 28, 31, // Jan, Feb, Mar
    30, 31, 30, // Apr, May, Jun
    31, 31, 30, // Jul, Aug, Sep
    31, 30, 31  // Oct, Nov, Dec
};

std::string months[] = {
    "January", "February", "March",
    "April", "May", "June",
    "July", "August", "September",
    "October", "November", "December"
};

int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        std::cout << "Usage:" << std::endl << "calendar MONTH <1-12> YEAR <1-9999>" << std::endl;
        return 0;
    } // HELP BLOCK

    if (argc != 3) {
        std::cout << "Invalid number of arguments. Please call 'calendar -h' for more information." << std::endl;
        return 0;
    }

    int month = std::stoi(argv[1]);
    int year = std::stoi(argv[2]);

    if (month > 12 || month < 1) {
        std::cout << "Month must be a numeric value between 1-12. Please try again." << std::endl;
        return 0;
    } if (year > 9999 || year < 1) {
        std::cout << "Year must be a numeric value between 1-9999. Please try again." << std::endl;
        return 0;
    }

    int dow = day_of_week(year, month, 1);

    if (dow == 0) dow = 7;

    display_calendar(dow, year, month);

    return 0;
}

int day_of_week(int year, int month, int day) {
    // Sakamoto's Algorithm
    int offsets[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4}; //30 - Sep, Ap, Jun, Nov

    if (month < 3) year -= 1;

    return ((year + year / 4 - year / 100 + year / 400 + offsets[month-1] + day) % 7);
}

void display_calendar(int dow, int year, int month) {
    std::cout << months[month-1] << " " << year << std::endl;
    std::cout << "Mo Tu We Th Fr Sa Su" << std::endl;
    int tracker = 8 - dow;

    for (int blank = 1; blank < dow; blank++) {
        std::cout << "   ";
    }

    for (int i = 1; i <= days_in_month[month-1]; i++) {
        if (i < 10) std::cout << " ";
        if (tracker > 1) {
            std::cout << i << " ";
            tracker--;
        } else {
            std::cout << i << std::endl;
            tracker = 7;
        }
    }
    std::cout << std::endl;
}