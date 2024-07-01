#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>

using namespace std;
class Date {
public:
    int day, month, year;

    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }
    void display() const {
        cout << setw(2) << setfill('0') << day << "/"
             << setw(2) << setfill('0') << month << "/"
             << year;
    }
};

class Event {
public:
    string description;
    Event(const string& desc) : description(desc) {}
    void display() const {
        cout << description;
    }
};

class Calendar {
private:
    map<Date, vector<Event>> events;
    int getDaysInMonth(int month, int year) const {
        static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (month == 2 && isLeapYear(year)) return 29;
        return daysInMonth[month - 1];
    }
    bool isLeapYear(int year) const {
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) return true;
        return false;
    }
    int dayOfWeek(int day, int month, int year) const {
        static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
        if (month < 3) year -= 1;
        return (year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7;
    }
public:
    void addEvent(const Date& date, const Event& event) {
        events[date].push_back(event);
    }
    void viewEvents(const Date& date) const {
        auto it = events.find(date);
        if (it != events.end()) {
            cout << "Events on ";
            date.display();
            cout << ":\n";
            for (const auto& event : it->second) {
                event.display();
                cout << endl;
            }
        } else {
            cout << "No events on ";
            date.display();
            cout << ".\n";
        }
    }
    void displayCalendar(int month, int year) const {
        static const char* monthNames[] = {
            "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"
        };
        cout << "     \n     " << monthNames[month - 1] << " " << year << "\n";
        cout << "Su Mo Tu We Th Fr Sa\n";
        int firstDay = dayOfWeek(1, month, year);
        int daysInMonth = getDaysInMonth(month, year);
        for (int i = 0; i < firstDay; ++i) {
            cout << "   ";
        }
        for (int day = 1; day <= daysInMonth; ++day) {
            cout << setw(2) << day << " ";
            if ((day + firstDay) % 7 == 0) cout << "\n";
        }
        if ((daysInMonth + firstDay) % 7 != 0) cout << "\n";
        for (const auto& entry : events) {
            if (entry.first.month == month && entry.first.year == year) {
                cout<<endl;
                cout << "Events on ";
                entry.first.display();
                cout << ":\n";
                for (const auto& event : entry.second) {
                    cout << "  - ";
                    event.display();
                    cout << "\n";
                }
            }
        }
    }
};

int main() {
    Calendar calendar;
    int choice;

    while (true) {
        cout << "\n1. Add Event\n2. View Events\n3. Display Calendar\n4. Exit\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int day, month, year;
            string description;
            cout << "Enter date (day month year): ";
            cin >> day >> month >> year;
            cin.ignore();
            cout << "Enter event description: ";
            getline(cin, description);
            Date date(day, month, year);
            Event event(description);
            calendar.addEvent(date, event);
            cout << "Event added.\n";
        } else if (choice == 2) {
            int day, month, year;
            cout << "Enter date (day month year): ";
            cin >> day >> month >> year;
            Date date(day, month, year);
            calendar.viewEvents(date);
        } else if (choice == 3) {
            int month, year;
            cout << "Enter month and year: ";
            cin >> month >> year;
            calendar.displayCalendar(month, year);
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
