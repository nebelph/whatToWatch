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
	int contains(std::string title) {
		for (int i = 0; i < list.size(); i++)
			if (list.at(i).getTitle() == title) return i;
		return -1;
	}
	void add(Activity const& a) {
		list.push_back(a);
	}
	void clear() {
		list.clear();
	}
	void remove(std::string title) {
		int index = contains(title);
		if (index != -1) list.erase(list.begin() + index);
	}
};

int main() {


	return 0;
}