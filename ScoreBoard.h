#pragma once
class ScoreBoard
{
private:
	ScoreBoard()=default;
	//std::vector<std::unique_ptr<Task>> tasks;
public:
	ScoreBoard(const ScoreBoard&) = delete;
	ScoreBoard operator=(const ScoreBoard&) = delete;
	static ScoreBoard& getInstance();

	/*void addTask(const Product& product, unsigned qty, double rewardBal, int rewardScore);
	bool removeTask(int taskId);

	void showTasks() const;
	Task* getTaskById(int taskId) const;

	void saveToFile(std::ostream& out) const;
	void loadFromFile(std::istream& in);*/

};

