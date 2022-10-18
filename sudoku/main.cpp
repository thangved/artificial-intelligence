#include <iostream>
#include <vector>

#define NUM_ROWS 9
#define NUM_COLS 9
#define MAX_VALUES 10
#define INF __INT_MAX__
#define SQUARE_SIZE 3
#define EMPTY 0

typedef struct
{
    int x, y;
} Coord;

typedef std::vector<Coord> ListCoord;

typedef struct
{
    bool data[NUM_COLS * NUM_ROWS][NUM_COLS * NUM_ROWS];
} Constraints;

Constraints create_constraints()
{
    Constraints Constraints = {{{}}};
    return Constraints;
}

int index_of(const Coord &coord)
{
    return coord.x * NUM_ROWS + coord.y;
}

Coord position_of(int vertex)
{
    Coord coord;

    coord.x = vertex / NUM_ROWS;
    coord.y = vertex % NUM_COLS;

    return coord;
}

bool add_constraint(Constraints &constraints, const Coord &s, const Coord &t)
{
    int u = index_of(s);
    int v = index_of(t);

    if (constraints.data[u][v])
    {
        return false;
    }

    constraints.data[u][v] = true;
    constraints.data[v][u] = true;

    return true;
}

ListCoord get_constraints(const Constraints &constraints, Coord coord)
{
    ListCoord result;
    int u = index_of(coord);

    for (int v = 0; v < NUM_COLS * NUM_ROWS; v++)
    {
        if (constraints.data[u][v])
        {
            result.push_back(position_of(v));
        }
    }

    return result;
}

typedef struct
{
    int cells[NUM_ROWS][NUM_COLS];
    Constraints constraints;
} Sudoku;

Sudoku create_sudoku()
{
    Sudoku sudoku = {{{}}, create_constraints()};

    return sudoku;
}

Sudoku create_sudoku_with_values(int inputs[NUM_ROWS][NUM_COLS])
{
    Sudoku sudoku = create_sudoku();

    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLS; j++)
        {
            sudoku.cells[i][j] = inputs[i][j];
        }
    }

    return sudoku;
}

void print_sudoku(const Sudoku &sudoku)
{
    std::cout << "Sudoku:\n";
    std::cout << "-----------------------------\n";
    for (int i = 0; i < NUM_ROWS; i++)
    {
        std::cout << "|";
        for (int j = 0; j < NUM_COLS; j++)
        {
            std::cout << " " << sudoku.cells[i][j] << " ";
        }
        std::cout << "|\n";
    }
    std::cout << "-----------------------------\n";
}

bool is_filled_sudoku(const Sudoku &sudoku)
{
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLS; j++)
        {
            if (!sudoku.cells[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

void spread_constraints_from(const Coord position, Constraints &constraints, ListCoord &changed_list)
{
    int row = position.x;
    int col = position.y;

    for (int i = 0; i < NUM_ROWS; i++)
    {
        if (i != row)
        {
            if (add_constraint(constraints, position, {i, col}))
                changed_list.push_back({i, col});
        }
    }

    for (int i = 0; i < NUM_COLS; i++)
    {
        if (i != col)
        {
            if (add_constraint(constraints, position, {row, i}))
                changed_list.push_back({row, i});
        }
    }

    for (int i = 0; i < SQUARE_SIZE; i++)
    {
        for (int j = 0; j < SQUARE_SIZE; j++)
        {
            int x = (row / SQUARE_SIZE) * SQUARE_SIZE;
            int y = (col / SQUARE_SIZE) * SQUARE_SIZE;

            if (x + i != row || y + j != col)
            {
                if (add_constraint(constraints, position, {x + i, y + j}))
                    changed_list.push_back({x + i, y + j});
            }
        }
    }
}

std::vector<int> get_available_values(const Coord &position, const Sudoku &sudoku)
{
    bool check[10];
    std::vector<int> result;
    for (int i = 0; i <= 9; i++)
    {
        check[i] = true;
    }

    check[0] = false;
    ListCoord constrains = get_constraints(sudoku.constraints, position);

    for (auto pos : constrains)
    {
        check[sudoku.cells[pos.x][pos.y]] = false;
    }

    for (int i = 1; i <= 9; i++)
    {
        if (check[i])
        {
            result.push_back(i);
        }
    }

    return result;
}

Coord get_next_empty_cell(const Sudoku &sudoku)
{
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLS; j++)
        {
            if (!sudoku.cells[i][j])
            {
                return {i, j};
            }
        }
    }

    return {};
}

Coord get_next_min_domain_cell(const Sudoku &sudoku)
{
    int min_length = INF;

    Coord result;

    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLS; j++)
        {
            if (sudoku.cells[i][j])
                continue;
            Coord pos = {i, j};
            int available_length = get_available_values(pos, sudoku).size();

            if (available_length < min_length)
            {
                min_length = available_length;
                result = pos;
            }
        }
    }

    return result;
}

bool sudoku_backtracking(Sudoku &sudoku)
{
    if (is_filled_sudoku(sudoku))
    {
        return true;
    }

    Coord position = get_next_min_domain_cell(sudoku);
    std::vector<int> available_list = get_available_values(position, sudoku);

    for (auto value : available_list)
    {
        sudoku.cells[position.x][position.y] = value;
        if (sudoku_backtracking(sudoku))
        {
            return true;
        }
        sudoku.cells[position.x][position.y] = EMPTY;
    }

    return false;
}

Sudoku solve_sudoku(Sudoku &sudoku)
{
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLS; j++)
        {
            ListCoord his;
            Coord pos = {i, j};
            spread_constraints_from(pos, sudoku.constraints, his);
        }
    }

    sudoku_backtracking(sudoku);

    return sudoku;
}

int main()
{
    int input[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};
    Sudoku sudoku = create_sudoku_with_values(input);

    Sudoku goal = solve_sudoku(sudoku);

    print_sudoku(goal);

    return 0;
}
