#include <iostream>
#include <vector>
#include <string> // to_string()
#include <Windows.h> // Sleep()
#include <math.h> // pow()

class Activity {
	std::string title_;
public:
	explicit Activity(std::string title) : title_(title) {}
	virtual std::string getTitle() const { return title_; }

};

//class Movie : public Activity {
//	unsigned year_;
//public:
//	Movie(std::string title, unsigned year) : Activity(title), year_(year) {}
//	std::string getTitle() const override {
//		return Activity::getTitle() + ", " + std::to_string(year_);
//	}
//};
//
//class Series : public Activity {
//	unsigned year_;
//public:
//	Series(std::string title, unsigned year) : Activity(title), year_(year) {}
//	std::string getTitle() const override {
//		return Activity::getTitle() + ", " + std::to_string(year_);
//	}
//};

class ActivityList {
	std::vector<Activity> list;
public:
	int contains(std::string title) const {
		for (int i = 0; i < list.size(); i++)
			if (list.at(i).getTitle() == title) return i;
		return -1;
	}
	unsigned size() const {
		return list.size();
	}
	Activity at(unsigned i) const {
		return list.at(i);
	}
	void add(std::string title) {
		if (contains(title) == -1) list.push_back(Activity(title));
	}
	void clear() {
		list.clear();
	}
	void remove(std::string title) {
		int index = contains(title);
		if (index != -1) list.erase(list.begin() + index);
	}
	void print() const {
		if (!size()) return;
		std::cout << "Your list:" << std::endl;
		for (auto const& i : list) {
  			std::cout << i.getTitle() << std::endl;
		}
	}
};

void spin(ActivityList const& al) {
	if (!al.size()) return;
	for (int i = 1; i < 20; i++) {
		Sleep(3 * pow(i, 1.8));
		std::cout << al.at(rand() % al.size()).getTitle() << std::endl;
	}
	std::cout << al.at(rand() % al.size()).getTitle() << " <-" << std::endl;
}

int exec() {
	std::cout << "to add:\t\t'-a <title>'\nto remove:\t'-r <title>'\nto print:\t'-p'\nto spin:\t'-s'\nto quit:\t'-q'\n";

	ActivityList al;
	std::string buffer;
	char c = '\0';
	bool run_status = true;
	do {
		while (std::cin.get(c)) {
			if (c != '\n') { // запись в буфер
				buffer.push_back(c);
			}
			else { // обработка буфера
				// удаление лишних пробелов
				if (buffer.empty()) continue;
				while (buffer.at(0) == ' ') {
					buffer.erase(buffer.begin());
				}
				// добавление
				if (buffer.at(0) == '-' && buffer.at(1) == 'a' && buffer.at(2) == ' ') {
					buffer.erase(buffer.begin(), buffer.begin() + 2);
					// удаление лишних пробелов
					while (buffer.size() && buffer.at(0) == ' ') {
						buffer.erase(buffer.begin());
					}
					std::cout << "Command: add (" << buffer << ")" << std::endl;
					al.add(buffer);
					buffer.clear();
				}
				// удаление
				else if (buffer.at(0) == '-' && buffer.at(1) == 'r' && buffer.at(2) == ' ') {
					buffer.erase(buffer.begin(), buffer.begin() + 2);
					// удаление лишних пробелов
					while (buffer.size() && buffer.at(0) == ' ') {
						buffer.erase(buffer.begin());
					}
					std::cout << "Command: remove (" << buffer << ")" << std::endl;
					al.remove(buffer);
					buffer.clear();
				}
				// вывод списка
				else if (buffer.at(0) == '-' && buffer.at(1) == 'p') {
					buffer.erase(buffer.begin(), buffer.begin() + 2);
					std::cout << "Command: print" << std::endl;
					al.print();
				}
				// вращение 
				else if (buffer.at(0) == '-' && buffer.at(1) == 's') {
					buffer.erase(buffer.begin(), buffer.begin() + 2);
					std::cout << "Command: spin" << std::endl;
					spin(al);
				}
				// выход
				else if (buffer.at(0) == '-' && buffer.at(1) == 'q') {
					buffer.erase(buffer.begin(), buffer.begin() + 2);
					std::cout << "Command: quit" << std::endl;
					run_status = false;
					break;
				}
				// не является командой
				else buffer.clear();
			}
		}
	} while (run_status);
	return 0;
}

int main() {
	srand(time(0));
	return exec();
}