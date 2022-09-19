#include <iostream>
#include <stack>
#include <queue>
#include <list>

#define MAX_TANKS 100
#define EMPTY 0
#define TARGET 8

typedef struct State
{
    int maxTanksCapacity[MAX_TANKS];
    int currentTanksCapacity[MAX_TANKS];
    int length;

    const struct Sate *parent;
} State;

State createState()
{
    State state;
    state.parent = NULL;
    state.length = 0;
    return state;
}

State cloneState(State state)
{
    State newState = createState();
    for (int i = 0; i < state.length; i++)
    {
        newState.maxTanksCapacity[i] = state.maxTanksCapacity[i];
        newState.currentTanksCapacity[i] = state.currentTanksCapacity[i];
    }
    newState.length = state.length;
    return state;
}

void addTank(int maxCapacity, State &state)
{
    state.maxTanksCapacity[state.length] = maxCapacity;
    state.currentTanksCapacity[state.length] = 0;
    state.length++;
}

bool pourWaterFromTankToOtherTank(const State *currentState, State &nextState, int from, int to)
{
    if (currentState->currentTanksCapacity[from] == EMPTY || currentState->currentTanksCapacity[to] == currentState->maxTanksCapacity[to])
    {
        return false;
    }

    int distance = std::min(currentState->currentTanksCapacity[from], currentState->maxTanksCapacity[to] - currentState->currentTanksCapacity[to]);

    nextState = cloneState(*currentState);
    nextState.currentTanksCapacity[from] -= distance;
    nextState.currentTanksCapacity[to] += distance;

    return true;
}

bool isGoal(const State &state)
{
    for (int i = 0; i < state.length; i++)
    {
        if (state.currentTanksCapacity[i] == TARGET)
        {
            return true;
        }
    }
    return false;
}

bool isLike(const State state1, const State state2)
{
    for (int i = 0; i < state1.length; i++)
    {
        if (state1.currentTanksCapacity[i] != state2.currentTanksCapacity[i])
        {
            return false;
        }
    }
    return true;
}

bool isExisting(std::list<const State *> st, const State &state)
{
    for (auto e : st)
    {
        for (int i = 0; i < state.length; i++)
        {
            if (isLike(*e, state))
            {
                return true;
            }
        }
    }
    return false;
}

const State *depthFirstSearch(const State &initialState)
{
    std::list<const State *> Open;
    std::list<const State *> Closed;

    Open.push_front(&initialState);
    while (!Open.empty())
    {
        const State *currentState = Open.front();
        Open.pop_front();
        Closed.push_front(currentState);
        if (isGoal(*currentState))
        {
            return currentState;
        }

        for (int i = 0; i < currentState->length; i++)
        {
            for (int j = 0; j < currentState->length; j++)
            {
                if (i == j)
                {
                    continue;
                }

                State nextState = createState();
                if (pourWaterFromTankToOtherTank(currentState, nextState, i, j))
                {
                    if (!isExisting(Closed, nextState))
                    {
                        State *pushState = (State *)malloc(sizeof(State));
                        *pushState = cloneState(nextState);
                        Open.push_front(pushState);
                    }
                }
            }
        }
    }

    return NULL;
}

int main()
{
    State state = createState();
    addTank(10, state);
    state.currentTanksCapacity[0] = 10;
    addTank(5, state);
    addTank(6, state);
    const State *goal = depthFirstSearch(state);
    return 0;
}