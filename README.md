Fitness Tracker
A simple console-based fitness tracking application written in C++. It supports multiple user profiles, workout logging, calorie goal tracking, and persistent data storage.

Features
Multi-user support — add and manage up to 10 user profiles
Workout logging — record workouts by type, duration, and calories burned
Custom workout types — extend the built-in list with your own categories
Calorie goals — set a personal calorie target and track progress
Persistent storage — all data is automatically saved to and loaded from `fitness_data.txt`

Getting Started

Prerequisites
A C++ compiler supporting C++11 or later (e.g. `g++`, `clang++`)

Build
bash
g++ -o fitness_tracker main.cpp

Run

bash
./fitness_tracker

Usage
When launched, you'll see the main menu:

=== Fitness Tracker Menu ===
1. Add User
2. Add Workout
3. View Workouts
4. Delete User
5. Set Calorie Goal
6. Exit


Menu Options
 1. Add User - Create a new user profile (up to 10 users) 
 2. Add Workout - Log a workout for a selected user 
 3. View Workouts - Display all workouts and calorie progress for a user 
 4. Delete User - Remove a user and their workout history 
 5. Set Calorie Goal - Set a daily/total calorie burn target for a user 
 6. Exit - Quit the application 


Built-in Workout Types
- Running
- Cycling
- Swimming
- Weight Training
- Yoga
- (Add your own custom types at runtime)


 Limits
 Users - 10 
 Workouts per user  100 
 Workout duration | 300 minutes 
 Calories per workout | 5,000 kcal 
 Workout types (incl. custom)  10 


Data Persistence
Data is automatically saved to `fitness_data.txt` in the working directory after any change (adding a workout, setting a goal, deleting a user). The file is loaded automatically on startup.


Project Structure
fitness_tracker/
├── main.cpp           # Full source code
├── fitness_data.txt   # Auto-generated data file (created on first save)
└── README.md


Class Overview
- Workout — stores workout type, duration, and calories
- Person — base class holding a user's name
- User  — manages a collection of workouts and a calorie goal


License
This project is provided as-is for educational purposes.
