#include <stdio.h>
#include <math.h>
#include <assert.h>

#include <string>
using std::string;

#include <iostream>
using std::cout;

#include <vector>
using std::vector;
#include <algorithm>

void debug_indent(int lvl) {for (int i{0}; i < lvl; ++i) {cout << "   ";}}


struct Mole
{
    int x;
    int y;
    int t;

    bool operator<(const Mole& other) {
        return this->t > other.t;
    }
};

struct Move
{
    int x;
    int y;

    bool operator<(const Move& other) {
        if (    (this->x < other.x) || 
                (this->x == other.x && this->y < other.y)
        ) {
            return true;
        } else {
            return false;
        }
    }
};

vector<Move> generate_moves(const int d)
{
    vector<Move> moves;
    for (int i{-d}; i <= d; ++i) {
        for (int j{-d}; j <= d; ++j) {
            if ( (i*i + j*j) <= d*d) {
                moves.push_back( {i,j} );
    }}}

    return moves;
}


struct Matrix
{
    bool *m;
    size_t width;
    int max_movement;
    
    Matrix(
        size_t _width,
        int _max_movement) :
        m(nullptr),
        width(_width),
        max_movement(_max_movement)
    {
        m = (bool*) malloc( (width*width) * sizeof(bool) );
        for (size_t i{0}; i < width*width; ++i) {
            *(m+i) = false;
        }
    };
    ~Matrix() {
        delete m;
    }


    void set(int x, int y, bool val) {
        size_t index = (x+max_movement)*width + (y+max_movement);
        m[index] = val;
    }

    bool get(int x, int y) const {
        size_t index = (x+max_movement)*width + (y+max_movement);
        return m[index];
    }

    void reinit(
            const int t,
            vector<Mole>::const_iterator new_moles,
            const vector<Mole>::const_iterator end_iter)
    {
        // Zero existing matrix
        for (size_t i{0}; i < width*width; ++i) {
            *(m+i) = false;
        }
        if (t != new_moles->t) { return; } // Exit after board clear if no moles are on board

        int current_time = new_moles->t;
        while (new_moles != end_iter && new_moles->t == current_time)
        {
            this->set(new_moles->x, new_moles->y, true);
            ++new_moles;
        }
    }

    void print()
    {
        for (size_t j{0}; j < width; ++j) {
            for (size_t i{0}; i < width; ++i) {
                printf("(%2lu,%2lu)=%d ", i, j, *((m+i*width)+j));
            }
            puts("");
        }
    }
};

const int MAX_T = 10;
const int MAX_W = 20;
const int MAX_MV = 5;


struct Memo
{
    int max_hits[MAX_T][MAX_W + 2*MAX_MV][MAX_W + 2*MAX_MV];
    const int max_time;
    const int board_width;
    const int max_movement;

    Memo(
        int _max_time,
        int _board_width,
        int _max_movement) : 
        max_time(_max_time),
        board_width(_board_width),
        max_movement(_max_movement)
    {
        for (int i{0}; i < max_time; ++i) {
            for (int j{0}; j < board_width+2*max_movement; ++j) {
                for (int k{0}; k < board_width+2*max_movement; ++k) {
                    max_hits[i][j][k] = 0;
                }
            }
        }
    }

    bool is_inside(int t, int x, int y) const {
        bool inside = (1 <= t && t <= max_time);
        inside &= (-max_movement <= x && x < board_width+max_movement);
        inside &= (-max_movement <= y && y < board_width+max_movement);

        return inside;
    }

    void set(int t, int x, int y, int val) {
        assert( this->is_inside(t, x, y) );
        max_hits[t-1][x+max_movement][y+max_movement] = val;
    }

    int get(int t, int x, int y) const {
        assert( this->is_inside(t, x, y) );
        return max_hits[t-1][x+max_movement][y+max_movement];
    }

    void print() 
    {
        for (int i{0}; i < max_time; ++i) {
            printf("T-%d:\n", i+1);
            printf("  : ");
            for(int k{0}; k < board_width+2*max_movement; ++k) {
                printf("%3d|", k-max_movement);
            }
            puts("");
            for (int j{0}; j < board_width+2*max_movement; ++j) {

                printf("%3d: ", j-max_movement);
                for (int k{0}; k < board_width+2*max_movement; ++k) {
                    printf("%3d ", max_hits[i][j][k]);
                }
                puts("\n");
            }
            puts("");
        }
    }
};

int max(int a, int b) {
    return (a < b) ? b : a;
}

int max_hits_from_position(
        const int t,
        const int max_t,
        const int x,
        const int y,
        const Memo& max_hits,
        const Matrix& active_moles,
        const vector<Move>& moves)
{
    int current_max = 0;
    for (const auto& move : moves)
    {
        int hits = 0;

        const int new_x = x + move.x;
        const int new_y = y + move.y;
        if ( !max_hits.is_inside(t, new_x, new_y) ) {
            continue; // Check new move if current moves whac way off board
        }

        // Check current pos
        if ( active_moles.get(x, y) ) {
            ++hits;
        }

        if ( !(move.x == 0 && move.y == 0) )
        {
            // Yes I know, it is lazy
            if (    (move.x%4 == 0 && move.y == 0) ||
                    (move.y%4 == 0 && move.x == 0))
            {
                const int it_x = (move.x/4);
                const int it_y = (move.y/4);

                if ( active_moles.get( (x + 1*it_x), (y + 1*it_y) ) ) {
                    ++hits;
                }
                if ( active_moles.get( (x + 2*it_x), (y + 2*it_y) ) ) {
                    ++hits;
                }
                if ( active_moles.get( (x + 3*it_x), (y + 3*it_y) ) ) {
                    ++hits;
                }
            }
            else if (move.x%2 == 0 && move.y%2 == 0)
            {
                const int it_x = (move.x/2);
                const int it_y = (move.y/2);

                if ( active_moles.get( (x + 1*it_x), (y + 1*it_y) ) ) {
                    ++hits;
                }
            }
            else if (move.x%3 == 0 && move.y%3 == 0)
            {
                const int it_x = (move.x/3);
                const int it_y = (move.y/3);

                if ( active_moles.get( (x + 1*it_x), (y + 1*it_y) ) ) {
                    ++hits;
                }
                if ( active_moles.get( (x + 2*it_x), (y + 2*it_y) ) ) {
                    ++hits;
                }
            }
            else if (   (move.x%5 == 0 && move.y == 0) ||
                        (move.y%5 == 0 && move.x == 0))
            {
                const int it_x = (move.x/5);
                const int it_y = (move.y/5);

                if ( active_moles.get( (x + 1*it_x), (y + 1*it_y) ) ) {
                    ++hits;
                }
                if ( active_moles.get( (x + 2*it_x), (y + 2*it_y) ) ) {
                    ++hits;
                }
                if ( active_moles.get( (x + 3*it_x), (y + 3*it_y) ) ) {
                    ++hits;
                }
                if ( active_moles.get( (x + 4*it_x), (y + 4*it_y) ) ) {
                    ++hits;
                }
            }

            // Check pos at end of line: new_x and new_y
            if ( active_moles.get(new_x, new_y) ) {
                ++hits;
            }
        }

        // Add destination if not at last timestep
        if (t < max_t) {
            hits += max_hits.get(t+1, new_x, new_y);
        }

        current_max = max(hits, current_max);
    }

    return current_max;
}

void test_case(
        const int n, // Width of board
        const int d, // Max distance of a move
        const int n_moles)
{
    int b_width = n + 2*d;
    Matrix active_moles(b_width, d);

    vector<Mole> moles;
    {
        int x, y, t;
        for (int i{0}; i < n_moles; ++i) {
            scanf("%d %d %d\n", &x, &y, &t);
            moles.push_back( {x, y, t} );
        }
    }
    std::sort(moles.begin(), moles.end());
  
    int timestamp_last_mole = moles.begin()->t;
  

    Memo max_hits(timestamp_last_mole, n, d);

    // Generate all valid moves for this test case
    vector<Move> moves = generate_moves(d);

    // Iterator to beginning of sequence of moles for the current timestamp
    vector<Mole>::const_iterator current_moles = moles.begin();

    int first_t = 1;
    for (int t{timestamp_last_mole}; 1 <= t; --t)
    {
        // Iterate to moles on this timestep or earlier one (backwards iteration through time)
        while ( (current_moles != moles.end()) &&
                (current_moles->t) > t)
        {
            ++current_moles;
        }
       
        // Break out early if mole list is emptied
        if (current_moles == moles.end())
        {
            first_t = t+1;
            break;
        }
        
        // Re-initialize active_moles: zero and set new moles
        active_moles.reinit(t, current_moles, moles.end());

        // 2D iteration over all possible start positions in (and outside) the board
        for (int i{-d}; i < n+d; ++i) {
            for (int j{-d}; j < n+d; ++j) {

                int max_val = max_hits_from_position(
                        t, timestamp_last_mole,
                        i, j,
                        max_hits,
                        active_moles,
                        moves);
                max_hits.set(t, i, j, max_val);
            }
        }

    }

    int max_val = 0;
    for (int i{-d}; i < n+d; ++i) {
        for (int j{-d}; j < n+d; ++j) {
            int val = max_hits.get(first_t, i, j);
            if (max_val < val) {
                max_val = val;
            }
        }
    }
    printf("%d\n", max_val);
}

int main()
{
    int n, d, m;

    while(1)
    {
        scanf("%d %d %d\n", &n, &d, &m);
        if (n+d+m == 0) { break; } // All zeroes (no negative values in file)

        test_case(n, d, m);
    }
}

