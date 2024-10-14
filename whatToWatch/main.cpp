#include <iostream>
#include <vector>

class Activity {
	std::string title_;
public:
	explicit Activity(std::string title) : title_(title) {}
	std::string getTitle() const { return title_; }

};

class Movie : public Activity {
	unsigned year_;
public:
	Movie(std::string title, unsigned year) : Activity(title), year_(year) {}
};

class Series : public Activity {
	unsigned year_;
public:
	Series(std::string title, unsigned year) : Activity(title), year_(year) {}
};

class ActivityList {
	std::vector<Activity> list;
public:
	int contains(std::string title) const {
		for (int i = 0; i < list.size(); i++)
			if (list.at(i).getTitle() == title) return i;
		return -1;
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
		for (auto const& i : list) {
  			std::cout << i.getTitle() << std::endl;
		}
	}
};

void spin(ActivityList const& al) {
	
}

int menu() {
	std::cout << "to add:\t\t'a <title>'\nto remove:\t'r <title>'\nto stop:\t's'\n";

	ActivityList al;
	std::string buffer;
	char c = '\0';
	bool status = 0; // 0 - нет ввода, 1 - ввод на добавление, 2 - ввод на удаление

	while (std::cin.get(c)) {
		if (c != '\n') { // запись в буфер
			buffer.push_back(c);
			//std::cout << c << " pushed to buffer" << std::endl;
		}
		else { // обработка буфера
			// удаление лишних пробелов
			if (buffer.empty()) continue;
			while (buffer.at(0) == ' ') {
				buffer.erase(buffer.begin());
				//std::cout << "' ' deleted from buffer" << std::endl;
			}
			// добавление
			if (buffer.at(0) == 'a' && buffer.at(1) == ' ') {
				// удаление команды 'a' из буфера
				buffer.erase(buffer.begin());
				// удаление лишних пробелов
				while (buffer.at(0) == ' ') {
					buffer.erase(buffer.begin());
					//std::cout << "' ' deleted from buffer" << std::endl;
				}
				std::cout << "Command: add (" << buffer << ")" << std::endl;
				al.add(buffer);
				//std::cout << buffer << " added to al" << std::endl;
				buffer.clear();
				//std::cout << "buffer cleared" << std::endl;
			}
			// удаление
			else if (buffer.at(0) == 'r' && buffer.at(1) == ' ') {
				buffer.erase(buffer.begin());
				// удаление лишних пробелов
				while (buffer.at(0) == ' ') {
					buffer.erase(buffer.begin());
					//std::cout << "' ' deleted from buffer" << std::endl;
				}
				std::cout << "Command: remove (" << buffer << ")" << std::endl;
				al.remove(buffer);
				//std::cout << buffer << " removed from al" << std::endl;
				buffer.clear();
				//std::cout << "buffer cleared" << std::endl;
			}
			// остановка
			else if (buffer.at(0) == 's') {
				std::cout << "Command: stop" << std::endl;
				break;
			}
			else {
				//std::cout << "wrong command!" << std::endl;
				buffer.clear();
				//std::cout << "buffer cleared" << std::endl;
			}

		}
	}
	al.print();
	return 0;
}

int exec() {
	return menu();
}

int main() {
	return exec();
}