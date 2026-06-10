#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

const int MAX_USERS = 10;
const int MAX_WORKOUTS = 100;
const int MAX_TYPES = 10;
const float MAX_DURATION = 300.0;
const int MAX_CALORIES = 5000;

string WORKOUT_TYPES[MAX_TYPES] = {"Running", "Cycling", "Swimming", "Weight Training", "Yoga"};
int WORKOUT_TYPE_COUNT = 5;

class Workout
{
protected:
    string type;
    float duration;
    float calories;

public:
    Workout() : type(""), duration(0), calories(0) {}
    Workout(string t, float d, float c) : type(t), duration(d), calories(c) {}

    string getType() const { return type; }
    float getDuration() const { return duration; }
    float getCalories() const { return calories; }

    void setType(string t) { type = t; }
    void setDuration(float d) { duration = d; }
    void setCalories(float c) { calories = c; }
};

class Person
{
protected:
    string name;

public:
    Person() : name("") {}
    Person(string n) : name(n) {}

    void setName(string n) { name = n; }
    string getName() const { return name; }
};

class User : public Person
{
private:
    Workout workouts[MAX_WORKOUTS];
    int workoutCount;
    float calorieGoal;

public:
    User() : Person(), workoutCount(0), calorieGoal(0) {}
    User(string n) : Person(n), workoutCount(0), calorieGoal(0) {}

    void addWorkout();
    void displayWorkouts();
    void setGoal();
    int getWorkoutCount() const { return workoutCount; }
    float getCaloriesGoal() const { return calorieGoal; }
    Workout getWorkout(int index) const { return workouts[index]; }

    void setData(string n, float goal, int count)
    {
        name = n;
        calorieGoal = goal;
        workoutCount = count;
    }

    void setWorkout(int index, string t, float d, float c)
    {
        if (index >= 0 && index < MAX_WORKOUTS)
            workouts[index] = Workout(t, d, c);
    }
};

User users[MAX_USERS];
int userCount = 0;

void User::addWorkout()
{
    if (workoutCount >= MAX_WORKOUTS)
    {
        cout << "Error: Maximum workouts reached!\n";
        return;
    }

    int choice;
    do
    {
        cout << "Select a workout type:\n";
        for (int i = 0; i < WORKOUT_TYPE_COUNT; i++)
        {
            cout << i + 1 << ". " << WORKOUT_TYPES[i] << endl;
        }
        cout << WORKOUT_TYPE_COUNT + 1 << ". Add Custom Type\n";
        cout << "Enter choice: ";
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > WORKOUT_TYPE_COUNT + 1)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid selection. Try again.\n";
        }
    } while (choice < 1 || choice > WORKOUT_TYPE_COUNT + 1);

    string workoutType;
    if (choice == WORKOUT_TYPE_COUNT + 1)
    {
        cin.ignore();
        cout << "Enter custom workout type: ";
        getline(cin, workoutType);
        if (WORKOUT_TYPE_COUNT < MAX_TYPES)
        {
            WORKOUT_TYPES[WORKOUT_TYPE_COUNT++] = workoutType;
        }
    }
    else
    {
        workoutType = WORKOUT_TYPES[choice - 1];
    }

    float duration, calories;
    do
    {
        cout << "Enter duration (max " << MAX_DURATION << " mins): ";
        cin >> duration;
        if (cin.fail() || duration <= 0 || duration > MAX_DURATION)
        {
            cout << "Invalid duration. Please enter a value between 1 and " << MAX_DURATION << " minutes.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    } while (duration <= 0 || duration > MAX_DURATION);

    do
    {
        cout << "Enter calories burned (max " << MAX_CALORIES << "): ";
        cin >> calories;
        if (cin.fail() || calories <= 0 || calories > MAX_CALORIES)
        {
            cout << "Invalid calories. Please enter a value between 1 and " << MAX_CALORIES << ".\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    } while (calories <= 0 || calories > MAX_CALORIES);

    workouts[workoutCount++] = Workout(workoutType, duration, calories);
    cout << "Workout added successfully!\n";
}

void User::displayWorkouts()
{
    if (workoutCount == 0)
    {
        cout << "No workouts recorded for " << name << ".\n";
        return;
    }
    cout << "\n=== Workouts for " << name << " ===\n";
    for (int i = 0; i < workoutCount; i++)
    {
        cout << i + 1 << ". " << workouts[i].getType() << " | Duration: " << workouts[i].getDuration()
             << " mins | Calories: " << workouts[i].getCalories() << " kcal\n";
    }
    if (calorieGoal > 0)
    {
        float total = 0;
        for (int i = 0; i < workoutCount; i++)
            total += workouts[i].getCalories();
        cout << "Total Calories Burned: " << total << " / Goal: " << calorieGoal << endl;
    }
}

void User::setGoal()
{
    cout << "Set your calorie goal: ";
    cin >> calorieGoal;
    cout << "Goal set to " << calorieGoal << " kcal.\n";
}

void saveData()
{
    ofstream file("fitness_data.txt");
    if (!file)
    {
        cout << "Failed to save data.\n";
        return;
    }
    file << userCount << "\n";
    for (int i = 0; i < userCount; i++)
    {
        file << users[i].getName() << "\n";
        file << users[i].getCaloriesGoal() << "\n";
        file << users[i].getWorkoutCount() << "\n";
        for (int j = 0; j < users[i].getWorkoutCount(); j++)
        {
            Workout w = users[i].getWorkout(j);
            file << w.getType() << "\n"
                 << w.getDuration() << " " << w.getCalories() << "\n";
        }
    }
    file.close();
}

void loadData()
{
    ifstream file("fitness_data.txt");
    if (!file)
        return;
    file >> userCount;
    file.ignore();
    for (int i = 0; i < userCount; i++)
    {
        string name;
        float goal;
        int count;
        getline(file, name);
        file >> goal;
        file >> count;
        file.ignore();
        users[i].setData(name, goal, count);
        for (int j = 0; j < count; j++)
        {
            string type;
            float dur, cal;
            getline(file, type);
            file >> dur >> cal;
            file.ignore();
            users[i].setWorkout(j, type, dur, cal);
        }
    }
    file.close();
}

void addUser()
{
    if (userCount >= MAX_USERS)
    {
        cout << "Error: Maximum users reached!\n";
        return;
    }
    cout << "Enter user name: ";
    cin.ignore();
    string name;
    getline(cin, name);
    users[userCount].setName(name);
    userCount++;
    cout << "User added successfully!\n";
    saveData();
}

int selectUser()
{
    if (userCount == 0)
    {
        cout << "No users available.\n";
        return -1;
    }
    for (int i = 0; i < userCount; i++)
    {
        cout << i + 1 << ". " << users[i].getName() << endl;
    }
    cout << "Select user: ";
    int index;
    cin >> index;
    if (index < 1 || index > userCount)
        return -1;
    return index - 1;
}

void deleteUser()
{
    int index = selectUser();
    if (index == -1)
        return;
    for (int i = index; i < userCount - 1; i++)
    {
        users[i] = users[i + 1];
    }
    userCount--;
    cout << "User deleted successfully!\n";
    saveData();
}

int main()
{
    loadData();
    while (true)
    {
        cout << "\n=== Fitness Tracker Menu ===\n";
        cout << "1. Add User\n2. Add Workout\n3. View Workouts\n4. Delete User\n5. Set Calorie Goal\n6. Exit\nChoice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            addUser();
            break;
        case 2:
        {
            int index = selectUser();
            if (index != -1)
                users[index].addWorkout();
            saveData();
            break;
        }
        case 3:
        {
            int index = selectUser();
            if (index != -1)
                users[index].displayWorkouts();
            break;
        }
        case 4:
            deleteUser();
            break;
        case 5:
        {
            int index = selectUser();
            if (index != -1)
                users[index].setGoal();
            saveData();
            break;
        }
        case 6:
            cout << "Goodbye!\n";
            return 0;
        default:
            cout << "Invalid option.\n";
        }
    }
    return 0;
}