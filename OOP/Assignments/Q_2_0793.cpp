#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

class Robot
{
    string robotName;
    int hits;

public:
    Robot() : robotName(""), hits(0) {}        // Default constructor
    Robot(string n) : robotName(n), hits(0) {} // Parameterized constructor

    void hitBall(int &ballX, int &ballY, const string &direction)
    {
        if (direction == "up")
        {
            ballY++;
        }
        else if (direction == "down")
        {
            ballY--;
        }
        else if (direction == "right")
        {
            ballX++;
        }
        else if (direction == "left")
        {
            ballX--;
        }
        else
        {
            cout << "Invalid direction entered!" << endl;
            return;
        }
        hits++; 
    }

    // Getter 
    int getHits() { return hits; }
    string getRobotName() { return robotName; }
};

class Ball
{
    int ball_x;
    int ball_y;

public:
    Ball() : ball_x(0), ball_y(0) {} // Default constructor

    // Getter  for ball position
    int getX() { return ball_x; }
    int getY() { return ball_y; }

    void move(int dx, int dy)
    {
        ball_x += dx;
        ball_y += dy;
    }

    pair<int, int> getPosition() const
    {
        return {ball_x, ball_y};
    }
};

class Goal
{
    const int goal_x = 3;
    const int goal_y = 3;

public:
    bool isGoalReached(int ballX, int ballY) const
    {
        return (goal_x == ballX && goal_y == ballY);
    }
};

class Team
{
    string teamName;

public:
    Robot *robot;
    Team() : teamName(""), robot(nullptr) {} // Default constructor
    Team(string n, Robot *r) : teamName(n), robot(r) {}

    // Getter  for team name
    string getTeamName() { return teamName; }

    ~Team()
    {
        robot = nullptr;
    }
};

class Game
{
    Team teamOne;
    Team teamTwo;
    Ball ball;
    Goal goal;

public:
    Game(Team t1, Team t2) : teamOne(t1), teamTwo(t2) {} // Parameterized constructor

    void startGame()
    {
        cout << "Let the games begin!!!" << endl;
        playTurn(&teamOne);
        ball = Ball(); // Reset ball position
        playTurn(&teamTwo);
        declareWinner();
    }

    void playTurn(Team *team)
    {
        cout << endl
             << "Team \"" << team->getTeamName() << "\" is playing now!" << endl;
        while (!goal.isGoalReached(ball.getX(), ball.getY()))
        {
            string dir;
            auto ballPosition = ball.getPosition();

            cout << "Current ball position: (" << ballPosition.first << ", " << ballPosition.second << ")" << endl;
            cout << "Enter the direction (up, down, left, right): ";
            getline(cin, dir);
            transform(dir.begin(), dir.end(), dir.begin(), ::tolower);

            team->robot->hitBall(ballPosition.first, ballPosition.second, dir);
            ball.move(ballPosition.first - ball.getX(), ballPosition.second - ball.getY());
        }

        cout << "Team \"" << team->getTeamName() << "\" took " << team->robot->getHits() << " hits to reach the goal." << endl;
    }

    void declareWinner()
    {
        cout << endl
             << "---- Game Result ----" << endl;
        if (teamOne.robot->getHits() < teamTwo.robot->getHits())
        {
            cout << "Team \"" << teamOne.getTeamName() << "\" with Robot \"" << teamOne.robot->getRobotName() << "\" wins with " << teamOne.robot->getHits() << " hits!" << endl;
        }
        else if (teamOne.robot->getHits() > teamTwo.robot->getHits())
        {
            cout << "Team \"" << teamTwo.getTeamName() << "\" with Robot \"" << teamTwo.robot->getRobotName() << "\" wins with " << teamTwo.robot->getHits() << " hits!" << endl;
        }
        else
        {
            cout << "The game ended in a tie!" << endl;
        }
    }
};

int main()
{
    int choice;
    while (1)
    {
        cout << endl
             << "Football Game Simulation" << endl;
        cout << "1. Start Game" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string robotName1, robotName2, teamName1, teamName2;
            cin.ignore();
            cout << "Enter Robot 1 name: ";
            getline(cin, robotName1);
            cout << "Enter Team 1 name: ";
            getline(cin, teamName1);

            cout << "Enter Robot 2 name: ";
            getline(cin, robotName2);
            cout << "Enter Team 2 name: ";
            getline(cin, teamName2);

            Robot robot1(robotName1);
            Robot robot2(robotName2);

            Team team1(teamName1, &robot1);
            Team team2(teamName2, &robot2);

            Game game(team1, team2);
            game.startGame();
            break;
        }

        case 2:
            cout << "Exiting the game..." << endl;
            return 0;

        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }
}