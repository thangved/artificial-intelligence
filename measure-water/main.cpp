#include <iostream>
#include <stack>
#include <queue>

#define MAX_TANK_CAPACITY_X 98
#define MAX_TANK_CAPACITY_Y 20
#define EMPTY 0
#define GOAL 14
#define ACTION_COUNT 6

using namespace std;

typedef struct State
{
    int x, y, action;
    const struct State *parent;
} State;

State createState(const State *parent)
{
    return State{0, 0, 0, parent};
}

bool isGoal(const State &state)
{
    return state.x == GOAL || state.y == GOAL;
}

bool pourWaterFullX(const State &currentState, State &nextState)
{
    if (currentState.x == MAX_TANK_CAPACITY_X)
    {
        return false;
    }
    nextState.x = MAX_TANK_CAPACITY_X;
    nextState.y = currentState.y;
    return true;
}

bool pourWaterFullY(const State &currentState, State &nextState)
{
    if (currentState.y == MAX_TANK_CAPACITY_Y)
    {
        return false;
    }
    nextState.x = currentState.x;
    nextState.y = MAX_TANK_CAPACITY_Y;
    return true;
}

bool pourWaterEmptyX(const State &currentState, State &nextState)
{
    if (currentState.x == EMPTY)
    {
        return false;
    }
    nextState.x = EMPTY;
    nextState.y = currentState.y;
    return true;
}

bool pourWaterEmptyY(const State &currentState, State &nextState)
{
    if (currentState.y == EMPTY)
    {
        return false;
    }
    nextState.x = currentState.x;
    nextState.y = EMPTY;
    return true;
}

bool pourWaterXY(const State &currentState, State &nextState)
{
    if (currentState.x == EMPTY || currentState.y == MAX_TANK_CAPACITY_Y)
    {
        return false;
    }

    int distance = min(MAX_TANK_CAPACITY_Y - currentState.y, currentState.x);
    nextState.x = currentState.x - distance;
    nextState.y = currentState.y + distance;
    return true;
}

bool pourWaterYX(const State &currentState, State &nextState)
{
    if (currentState.y == EMPTY || currentState.x == MAX_TANK_CAPACITY_X)
    {
        return false;
    }

    int distance = min(MAX_TANK_CAPACITY_X - currentState.x, currentState.y);
    nextState.x = currentState.x + distance;
    nextState.y = currentState.y - distance;

    return true;
}

bool callOperator(const State &currentState, State &nextState, int action)
{
    nextState.action = action;
    switch (action)
    {
    case 1:
        return pourWaterFullX(currentState, nextState);
    case 2:
        return pourWaterFullY(currentState, nextState);
    case 3:
        return pourWaterEmptyX(currentState, nextState);
    case 4:
        return pourWaterEmptyY(currentState, nextState);
    case 5:
        return pourWaterXY(currentState, nextState);
    case 6:
        return pourWaterYX(currentState, nextState);

    default:
        cout << "Invalid action!!!";
        return false;
    }
}

const State *depthFirstSearch(const State &initState)
{
    bool OPEN_STATES[MAX_TANK_CAPACITY_X + 1][MAX_TANK_CAPACITY_Y + 1] = {{}};
    bool CLOSED_STATES[MAX_TANK_CAPACITY_X + 1][MAX_TANK_CAPACITY_Y + 1] = {{}};

    stack<const State *> Open;

    Open.push(&initState);

    OPEN_STATES[initState.x][initState.y] = true;

    while (!Open.empty())
    {
        const State *currentState = Open.top();
        Open.pop();
        CLOSED_STATES[currentState->x][currentState->y] = true;

        if (isGoal(*currentState))
        {
            return currentState;
        }

        for (int i = 1; i <= ACTION_COUNT; i++)
        {
            State nextState = createState(currentState);
            if (callOperator(*currentState, nextState, i))
            {
                if (CLOSED_STATES[nextState.x][nextState.y])
                    continue;
                State *pushState = (State *)malloc(sizeof(State));
                pushState->x = nextState.x;
                pushState->y = nextState.y;
                pushState->action = nextState.action;
                pushState->parent = currentState;
                Open.push(pushState);
                OPEN_STATES[nextState.x][nextState.y] = true;
            }
        }
    }
    return NULL;
}

const State *breathFirstSearch(const State &initState)
{
    bool OPEN_STATES[MAX_TANK_CAPACITY_X + 1][MAX_TANK_CAPACITY_Y + 1] = {{}};
    bool CLOSED_STATES[MAX_TANK_CAPACITY_X + 1][MAX_TANK_CAPACITY_Y + 1] = {{}};

    queue<const State *> Open;

    Open.push(&initState);

    OPEN_STATES[initState.x][initState.y] = true;

    while (!Open.empty())
    {
        const State *currentState = Open.front();
        Open.pop();
        CLOSED_STATES[currentState->x][currentState->y] = true;

        if (isGoal(*currentState))
        {
            return currentState;
        }

        for (int i = 1; i <= ACTION_COUNT; i++)
        {
            State nextState = createState(currentState);
            if (callOperator(*currentState, nextState, i))
            {
                if (OPEN_STATES[nextState.x][nextState.y] || CLOSED_STATES[nextState.x][nextState.y])
                    continue;
                State *pushState = (State *)malloc(sizeof(State));
                pushState->x = nextState.x;
                pushState->y = nextState.y;
                pushState->action = nextState.action;
                pushState->parent = currentState;
                Open.push(pushState);
                OPEN_STATES[nextState.x][nextState.y] = true;
            }
        }
    }
    return NULL;
}

void printState(State state)
{
    cout << "Action:\t";
    switch (state.action)
    {
    case 0:
        cout << "Initial state";
        break;
    case 1:
        cout << "Full X";
        break;
    case 2:
        cout << "Full Y";
        break;
    case 3:
        cout << "Empty X";
        break;
    case 4:
        cout << "Empty Y";
        break;
    case 5:
        cout << "X to Y";
        break;
    case 6:
        cout << "Y to X";
        break;

    default:
        cout << "Invalid action!!";
        break;
    }
    cout << endl;
    cout << "State:\tX: " << state.x << ", Y: " << state.y << endl;
    cout << "----------------------" << endl;
}

void printStates(const State *state)
{
    if (state == NULL)
    {
        return;
    }
    printStates(state->parent);
    printState(*state);
}

int main()
{
    const State firstState = createState(NULL);
    const State *goalState = depthFirstSearch(firstState);
    if (goalState == NULL)
    {
        cout << "No Solution" << endl;
    }
    printStates(goalState);
    return 0;
}
