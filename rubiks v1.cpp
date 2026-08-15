#include <bits/stdc++.h>
using namespace std;

const unsigned centers[] = {4,22,25,28,31,49};
const unsigned inception[6] = {0,4,2,5,3,1};

const unsigned edgelist[][2] = {{7,13}, {5,16}, {1,19}, {3,10}, {26,27}, {30,29}, {32,21}, {24,23}, {46,37}, {50,40}, {52,43}, {48,34}};
const unsigned vertlist[][3] = {{8,14,15},{2,18,17}, {0,20,9}, {6,12,11}, {47,38,39}, {53,42,41}, {51,44,33}, {45,36,35}};

unsigned edgemap[36] = {0,0,0,2,3,1,0,0,8,10,11,9,16,24,0,8,7,4,18,26,24,0,6,5,19,27,23,22,0,6,17,25,20,21,22,0};
unsigned vertmap[8] = {3,0,2,1,7,4,6,5};

// [move, index] = index
unsigned edgemovetable[18][12] = {{3,0,1,2,4,5,6,7,8,9,10,11},{0,1,2,3,4,5,6,7,9,10,11,8},{4,1,2,3,8,5,6,0,7,9,10,11},{0,1,6,3,4,2,10,7,8,9,5,11},{0,1,2,7,4,5,3,11,8,9,10,6},{0,5,2,3,1,9,6,7,8,4,10,11},{2,3,0,1,4,5,6,7,8,9,10,11},
                                  {0,1,2,3,4,5,6,7,10,11,8,9},{8,1,2,3,7,5,6,4,0,9,10,11},{0,1,10,3,4,6,5,7,8,9,2,11},{0,1,2,11,4,5,7,6,8,9,10,3},{0,9,2,3,5,4,6,7,8,1,10,11},{1,2,3,0,4,5,6,7,8,9,10,11},{0,1,2,3,4,5,6,7,11,8,9,10},
                                  {7,1,2,3,0,5,6,8,4,9,10,11},{0,1,5,3,4,10,2,7,8,9,6,11},{0,1,2,6,4,5,11,3,8,9,10,7},{0,4,2,3,9,1,6,7,8,5,10,11}};
unsigned vertmovetable[18][8] = {{1,0,3,2,4,5,6,7},{0,1,2,3,7,6,5,4},{3,1,2,0,7,5,6,4},{0,5,6,3,4,1,2,7},{0,1,6,7,4,5,2,3},{1,0,2,3,5,4,6,7},{0,1,2,3,4,5,6,7},{0,1,2,3,4,5,6,7},{0,1,2,3,4,5,6,7},{0,1,2,3,4,5,6,7},{0,1,2,3,4,5,6,7},
                                 {0,1,2,3,4,5,6,7},{1,0,3,2,4,5,6,7},{0,1,2,3,7,6,5,4},{3,1,2,0,7,5,6,4},{0,5,6,3,4,1,2,7},{0,1,6,7,4,5,2,3},{1,0,2,3,5,4,6,7}};

// [move, index, orientation] = orientation;
unsigned edgemoveorient[18][12][2] = {{{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1}},{{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1}},
                                      {{1,0},{0,1},{0,1},{0,1},{1,0},{0,1},{0,1},{1,0},{1,0},{0,1},{0,1},{0,1}},{{0,1},{0,1},{1,0},{0,1},{0,1},{1,0},{1,0},{0,1},{0,1},{0,1},{1,0},{0,1}},
                                      {{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1}},{{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1}},
                                      {{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1}},{{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1}},
                                      {{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1}},{{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1}},
                                      {{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1}},{{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1}},
                                      {{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1}},{{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1}},
                                      {{1,0},{0,1},{0,1},{0,1},{1,0},{0,1},{0,1},{1,0},{1,0},{0,1},{0,1},{0,1}},{{0,1},{0,1},{1,0},{0,1},{0,1},{1,0},{1,0},{0,1},{0,1},{0,1},{1,0},{0,1}},
                                      {{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1}},{{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1}}};
unsigned vertmoveorient[18][8][3] = {{{0,2,1},{0,2,1},{0,2,1},{0,2,1},{0,1,2},{0,1,2},{0,1,2},{0,1,2}},{{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,2,1},{0,2,1},{0,2,1},{0,2,1}},{{2,1,0},{0,1,2},{0,1,2},{2,1,0},{2,1,0},{0,1,2},{0,1,2},{2,1,0}},
                                     {{0,1,2},{2,1,0},{2,1,0},{0,1,2},{0,1,2},{2,1,0},{2,1,0},{0,1,2}},{{0,1,2},{0,1,2},{1,0,2},{1,0,2},{0,1,2},{0,1,2},{1,0,2},{1,0,2}},{{1,0,2},{1,0,2},{0,1,2},{0,1,2},{1,0,2},{1,0,2},{0,1,2},{0,1,2}},
                                     {{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2}},{{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2}},{{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2}},
                                     {{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2}},{{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2}},{{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2}},
                                     {{0,2,1},{0,2,1},{0,2,1},{0,2,1},{0,1,2},{0,1,2},{0,1,2},{0,1,2}},{{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,2,1},{0,2,1},{0,2,1},{0,2,1}},{{2,1,0},{0,1,2},{0,1,2},{2,1,0},{2,1,0},{0,1,2},{0,1,2},{2,1,0}},
                                     {{0,1,2},{2,1,0},{2,1,0},{0,1,2},{0,1,2},{2,1,0},{2,1,0},{0,1,2}},{{0,1,2},{0,1,2},{1,0,2},{1,0,2},{0,1,2},{0,1,2},{1,0,2},{1,0,2}},{{1,0,2},{1,0,2},{0,1,2},{0,1,2},{1,0,2},{1,0,2},{0,1,2},{0,1,2}}};

struct prng_input {} RNG;
int TRACEBACK;
long long nodes_visited;
struct cube
{
    static cube solved;

    int score;
    short move_count, prev_move;
    unsigned long long edges=0, verts=0;

    // Loading
    static unsigned long long translate_edge(int x, int y) { return edgemap[6*x+y]; }
    static unsigned long long translate_vert(int x, int y, int z)
    {
        int base = vertmap[4*(x&1)+2*(y&1)+(z&1)];
        if (x<y && x<z) return base;
        if (y<z) return base|8;
        return base|16;
    }
    static cube from_input()
    {
        char input[55];
        unsigned translate[256];
        for (int i=0; i<54; i++) scanf("%s", input+i);
        for (int i=0; i<6; i++) translate[(int)input[centers[i]]] = inception[i];
        for (int i=0; i<54; i++) input[i] = translate[(int)input[i]];
        unsigned long long edges=0, verts=0;
        for (int i=0; i<12; i++) edges |= translate_edge(input[edgelist[i][0]], input[edgelist[i][1]])<<(5*i);
        for (int i=0; i< 8; i++) verts |= translate_vert(input[vertlist[i][0]], input[vertlist[i][1]], input[vertlist[i][2]])<<(5*i);
        return cube(edges, verts);
    }
    cube(long long edges, long long verts, int mc=0, int pm=-1) : score(get_score(edges, verts, mc)), move_count(mc), prev_move(pm), edges(edges), verts(verts) {}
    static cube random_cube(int scramble=30, int seed=-1)
    {
        seed += time(NULL);
        printf("Random cube with seed "); cout << seed << '\n';
        srand(seed);
        for (int i=0; i<100; i++) rand();

        long long edges = solved.edges;
        long long verts = solved.verts;
        for (int i=0; i<scramble; i++)
        {
            cube next = cube(edges, verts).make_move(rand()%18);
            edges = next.edges;
            verts = next.verts;
        }
        return cube(edges, verts);
    }

    // Debug and sorting
    void print(void)
    {
        printf("%llx %llx\n", edges, verts);
        cout << bitset<64>(edges) << '\n' << bitset<64>(verts) << '\n';
    }
    bool operator==(const cube &other) const
    {
        return edges == other.edges && verts == other.verts;
    }
    auto operator<=>(const cube &other) const
    {
        if (score != other.score) return score <=> other.score;
        if (edges != other.edges) return edges <=> other.edges;
        return verts <=> other.verts;
        // we prune duplicates and accept that we may keep the longer path
    }

    // Move making
    cube make_move(int moveid)
    {
        unsigned long long ecopy = edges, new_edges=0, new_verts=0;
        for (int i=0; i<12; i++)
        {
            unsigned long long new_thing = (ecopy&15) | (edgemoveorient[moveid][i][1&(ecopy>>4)]<<4);
            new_edges |= new_thing << (5*edgemovetable[moveid][i]);
            ecopy >>= 5;
        }
        ecopy = verts; // ahh yes edge copy = vertices great thinking idiot
        for (int i=0; i<8; i++)
        {
            unsigned long long new_thing = (ecopy&7) | (vertmoveorient[moveid][i][3&(ecopy>>3)]<<3);
            new_verts |= new_thing << (5*vertmovetable[moveid][i]);
            ecopy >>= 5;
        }
        return cube(new_edges, new_verts, move_count+1, moveid);
    }

    // Score function
    static int get_score(unsigned long long edges, unsigned long long verts, int move_count)
    {
        int score = -10 * move_count;
        if (edges == solved.edges && verts == solved.verts)
        {
            TRACEBACK = 1;
            return INT_MAX - move_count;
        }
        unsigned long long ecopy = edges;
        for (int i=0; i<12; i++)
        {
            if ((int)(ecopy&31) == i) score += 100; // 100 points for correct edge in correct orientation
            ecopy >>= 5;
        }
        ecopy = verts;
        for (int i=0; i<8; i++)
        {
            if ((int)(ecopy&31) == i) score += 100; // 100 points for correct vertex in correct orientation
            ecopy >>= 5;
        }
        return score;
    }
}
cube::solved(0x5a928398a418820, 0x398a418820);
namespace std
{
    template <> struct hash<cube>
    {
        size_t operator()(const cube &c) const noexcept
        {
            size_t h1 = hash<long long>{}(c.edges);
            size_t h2 = hash<long long>{}(c.verts);
            return h1^(h2+0x9e3779b9+(h1<<6)+(h1>>2));
        }
    };
}



/// Greedy search
pair<int,int> flat_search(cube cur, int iters, int prev_move)
{
    nodes_visited++;
    if (!iters) return {prev_move, cur.score};

    int best_move=prev_move, best_score=cur.score;
    for (int i=0; i<18; i++)
    {
        if (prev_move>=0)
        {
            if (i%6 == prev_move%6) continue;
            if ((prev_move-i+30)%6 == 1 && prev_move%6) continue;
        }
        auto [_,s] = flat_search(cur.make_move(i), iters-1, i);
//        if (TRACEBACK)
//        {
//            printf("Received iters %d = %d %d\n", iters, i, s);
//            return {i,s};
//        }
        if (s > best_score) { best_move = i; best_score = s; }
    }
    return {best_move, best_score};
}
int deep_search(cube cur, int best_score, int prev_move)
{
    printf("deep search on depth %d, score is %d\n", cur.move_count, best_score);
    if (cur == cube::solved) return 1;
    for (int depth=6; depth<=6; depth++)
    {
        auto [m,s] = flat_search(cur, depth, prev_move);
//        printf("wtf %d %d\n", m, s);
        TRACEBACK = 0;
        if (s < INT_MAX-1000 && s <= best_score) continue;

//        printf("Found with depth %d score %d\n", depth, s);
        int res = deep_search(cur.make_move(m), s, m);
        if (res) return res+1;
        return 0;
    }
    return 0;
}


/// Memory-bounded with heuristic
/*
We use an inadmissible heuristic for the rubik's cube, scoring each position by how much progress it seems to have made.
Given enough memory, we would perform a normal best-first search. However, we have a limited amount of memory for both the OPEN and CLOSED lists.
When either of these limits are surpassed, the worst state in either list is removed. Because of tight memory constraints, the likelihood that we would
have to backtrack to the removed states is so low that it is not worth adding tracking information to the parents, unlike in the SMA* algorithm.
We assume that the search space of the remaining options in OPEN contains a solution, or if not then enough possibilities to consume our time limit.
We assume that it unlikely we will come across the worst element in the closed list, since the space we are searching has better heuristics.
Lastly, since this algorithm may get stuck in a situation where our OPEN set is filled with items of equal heuristics and every next step is slightly worse,
we may want to temporarily boost the value of new states so they get explored at list a bit before being thrown away.
This can be done with heuristic priorities, or a complete dfs scan to a small depth.

Possible optimizations: DEPQ for OPEN, boost::unrodered_flat_set
*/
set<cube,greater<cube>> OPEN;
unordered_set<cube> CLOSED;
priority_queue<cube,vector<cube>,greater<cube>> CLOSED_search;
const int OPEN_MAX = 1e7;
const int CLOSED_MAX = 1e6;
int cutoff_score, minimum_score;

priority_queue<cube> FLAT_results;
const int FLAT_MAX = 1;
void MBBFS_flat_search(cube cur, int iters)
{
    nodes_visited++;
    if (!iters) return;

    for (int i=0; i<18; i++)
    {
        if (cur.prev_move >= 0)
        {
            if (i%6 == cur.prev_move%6) continue;
            if ((cur.prev_move-i+30)%6 == 1 && cur.prev_move%6) continue;
        }
        cube next = cur.make_move(i);
        if (CLOSED.count(next)) continue;
        if (cur.score > cutoff_score)
        {
            FLAT_results.push(next);
            if (FLAT_results.size() > FLAT_MAX) FLAT_results.pop();
        }
        if (cur.score > minimum_score) MBBFS_flat_search(next, iters-1); // only searchif we haven't ruined our score by too much
    }
}
int MBBFS_2(cube start)
{
    OPEN.clear();
    CLOSED.clear();
    CLOSED_search = {};
    OPEN.insert(start);
    int MBBFS_iters = 0;

    while (MBBFS_iters < 500 && !OPEN.empty())
    {
        cube cur = OPEN.extract(OPEN.begin()).value();
        nodes_visited++;
        MBBFS_iters++;
        if (OPEN.size() > OPEN_MAX/2) cutoff_score = OPEN.rbegin()->score;
        else cutoff_score = INT_MIN+1000;
        minimum_score = cutoff_score - 1000;
        if (MBBFS_iters % 100 == 0)
        {
            printf("Visited %lld nodes\n", nodes_visited);
            printf("Currently exploring %d, depth %d\n", cur.score, cur.move_count);
            printf("Sizes are %d/%d and %d/%d (%d)\n", OPEN.size(), OPEN_MAX, CLOSED.size(), CLOSED_MAX, CLOSED_search.size());
        }
        if (cur == cube::solved) return cur.move_count;
        MBBFS_flat_search(cur, 6);
        while (!FLAT_results.empty())
        {
            OPEN.insert(FLAT_results.top());
            FLAT_results.pop();
        }

        while (OPEN.size() > OPEN_MAX) OPEN.erase(prev(OPEN.end()));

        CLOSED.insert(cur);
        CLOSED_search.push(cur);
        while (CLOSED.size() > CLOSED_MAX)
        {
            CLOSED.erase(CLOSED_search.top());
            CLOSED_search.pop();
        }
    }
    return 0;
}

const int trials = 10;
int wincount;
int total_moves, min_moves=INT_MAX, max_moves;
double total_time, min_time=INT_MAX, max_time;

int main(void)
{
    for (int t=0; t<trials; t++)
    {
        cube start = cube::random_cube(10, t);
        clock_t start_t = clock();
//        int moves = deep_search(start, start.score, -1);
        int moves = MBBFS_2(start);
        clock_t end_t = clock();
        wincount += !!moves;
        double time = (double)(end_t-start_t)/CLOCKS_PER_SEC;
        if (moves)
        {
            total_moves += moves;
            min_moves = min(min_moves, moves);
            max_moves = max(max_moves, moves);
        }
        total_time += time;
        min_time = min(min_time, time);
        max_time = max(max_time, time);
    }

    printf("Visited %lld nodes\n", nodes_visited);
    printf("Success rate %d/%d = %g%%\n", wincount, trials, (double)wincount/trials*100);
    printf("min/avg/max moves: %d / %.2g / %d\n", min_moves, (double)total_moves/wincount, max_moves);
    printf("min/avg/max time: %.2fs / %.2fs / %.2fs\n", min_time, total_time/trials, max_time);
    return 0;
}
