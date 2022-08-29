#include <iostream>
#include <vector>

#define MAX_WEIGHT_A 9
#define MAX_WEIGHT_B 4
#define TARGET 6

typedef struct
{
    int x, y;
} State;

struct Node
{
    State state;
    struct Node *parent;
};

typedef struct Node *Tree;

Tree createRoot()
{
    Tree root = (Tree)malloc(sizeof(struct Node));

    root->state.x = 0;
    root->state.y = 0;
    root->parent = NULL;

    return root;
}

Tree findChildNode(Tree parent, State(action(State parentState)))
{
    Tree childNode = createRoot();
    childNode->parent = parent;
    childNode->state = action(parent->state);

    return childNode;
}

namespace action
{
    State fillA(State parentState)
    {
        parentState.x = MAX_WEIGHT_A;
        return parentState;
    }
    State fillB(State parentState)
    {
        parentState.y = MAX_WEIGHT_A;
        return parentState;
    }
    State aToB(State parentState)
    {
        int swappable = std::min(parentState.x, MAX_WEIGHT_B - parentState.y);
        parentState.x -= swappable;
        parentState.y += swappable;

        return parentState;
    }

    State bToA(State parentState)
    {
        int swappable = std::min(parentState.y, MAX_WEIGHT_A - parentState.x);
        parentState.y -= swappable;
        parentState.x += swappable;

        return parentState;
    }

    State emptyA(State parentState)
    {
        parentState.x = 0;
        return parentState;
    }

    State emptyB(State parentState)
    {
        parentState.y = 0;
        return parentState;
    }
}

bool isGoal(State state)
{
    return state.x == TARGET || state.y == TARGET;
}

bool statesIsEquals(State state1, State state2)
{
    return state1.x == state2.x && state1.y == state2.y;
}

bool stateIsExisting(std::vector<Tree> queue, State state)
{
    for (auto node = queue.begin(); node != queue.end(); node++)
    {
        if (statesIsEquals(state, (*node)->state))
        {
            return true;
        }
    }

    return false;
}

void printSolution(Tree last)
{
    if (last->parent == NULL)
    {
        std::cout << "(" << last->state.x << ", " << last->state.y << ")";
        return;
    }

    printSolution(last->parent);

    std::cout << " -> (" << last->state.x << ", " << last->state.y << ")";
}

void solution(Tree root)
{
    std::vector<Tree> Open, Closed;

    Open.push_back(root);
    while (!Open.empty())
    {
        Tree front = Open.front();
        Open.erase(Open.begin());
        Closed.push_back(front);

        if (isGoal(front->state))
        {
            break;
        }

        std::vector<Tree> childs;

        childs.push_back(findChildNode(front, action::aToB));
        childs.push_back(findChildNode(front, action::bToA));
        childs.push_back(findChildNode(front, action::fillA));
        childs.push_back(findChildNode(front, action::fillB));
        childs.push_back(findChildNode(front, action::emptyA));
        childs.push_back(findChildNode(front, action::emptyB));

        for (auto child = childs.begin(); child != childs.end(); child++)
        {
            if (!stateIsExisting(Open, (*child)->state) && !stateIsExisting(Closed, (*child)->state))
            {
                Open.push_back(*child);
            }
        }
    }

    printSolution(*(Closed.end() - 1));
}

int main()
{
    Tree root = createRoot();
    solution(root);
    return 0;
}
