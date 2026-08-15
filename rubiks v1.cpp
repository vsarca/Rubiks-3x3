#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

struct timer_class
{
    double last = 0;
    clock_t time = std::clock();
    timer_class &clock(void)
    {
        clock_t new_time = std::clock();
        last = (double)(new_time-time)/CLOCKS_PER_SEC;
        time = new_time;
        return *this;
    }
    double operator()(void) { return last; }
} timer;

/// Crap ton of hardcoded data

const char move_names[][3] = {"U","D","F","B","L","R","U2","D2","F2","B2","L2","R2","U'","D'","F'","B'","L'","R'"};

const unsigned centers[] = {4,49,25,31,22,28};

const unsigned edgelist[][2] = {{7,13}, {5,16}, {1,19}, {3,10}, {26,27}, {30,29}, {32,21}, {24,23}, {46,37}, {50,40}, {52,43}, {48,34}};
const unsigned vertlist[][3] = {{8,14,15}, {2,18,17}, {0,20,9}, {6,12,11}, {45,36,35}, {47,38,39}, {53,42,41}, {51,44,33}};

unsigned edgemap[36] = {0,0,0,2,3,1,0,0,8,10,11,9,16,24,0,8,7,4,18,26,24,0,6,5,19,27,23,22,0,6,17,25,20,21,22,0};
unsigned vertmap[8] = {3,0,2,1,4,5,7,6};

// [move, index] = index
unsigned edgemovetable[18][12] = {{3,0,1,2,4,5,6,7,8,9,10,11},{0,1,2,3,4,5,6,7,9,10,11,8},{4,1,2,3,8,5,6,0,7,9,10,11},{0,1,6,3,4,2,10,7,8,9,5,11},{0,1,2,7,4,5,3,11,8,9,10,6},{0,5,2,3,1,9,6,7,8,4,10,11},{2,3,0,1,4,5,6,7,8,9,10,11},
                                  {0,1,2,3,4,5,6,7,10,11,8,9},{8,1,2,3,7,5,6,4,0,9,10,11},{0,1,10,3,4,6,5,7,8,9,2,11},{0,1,2,11,4,5,7,6,8,9,10,3},{0,9,2,3,5,4,6,7,8,1,10,11},{1,2,3,0,4,5,6,7,8,9,10,11},{0,1,2,3,4,5,6,7,11,8,9,10},
                                  {7,1,2,3,0,5,6,8,4,9,10,11},{0,1,5,3,4,10,2,7,8,9,6,11},{0,1,2,6,4,5,11,3,8,9,10,7},{0,4,2,3,9,1,6,7,8,5,10,11}};
unsigned vertmovetable[18][8] = {{3,0,1,2,4,5,6,7},{0,1,2,3,5,6,7,4},{5,1,2,0,3,4,6,7},{0,2,7,3,4,5,1,6},{0,1,3,4,7,5,6,2},{1,6,2,3,4,0,5,7},{2,3,0,1,4,5,6,7},{0,1,2,3,6,7,4,5},{4,1,2,5,0,3,6,7},{0,7,6,3,4,5,2,1},{0,1,4,7,2,5,6,3},
                                 {6,5,2,3,4,1,0,7},{1,2,3,0,4,5,6,7},{0,1,2,3,7,4,5,6},{3,1,2,4,5,0,6,7},{0,6,1,3,4,5,7,2},{0,1,7,2,3,5,6,4},{5,0,2,3,4,6,1,7}};

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
unsigned vertmoveorient[18][8][3] = {{{0,2,1},{0,2,1},{0,2,1},{0,2,1},{0,1,2},{0,1,2},{0,1,2},{0,1,2}},{{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,2,1},{0,2,1},{0,2,1},{0,2,1}},{{2,1,0},{0,1,2},{0,1,2},{2,1,0},{2,1,0},{2,1,0},{0,1,2},{0,1,2}},
                                     {{0,1,2},{2,1,0},{2,1,0},{0,1,2},{0,1,2},{0,1,2},{2,1,0},{2,1,0}},{{0,1,2},{0,1,2},{1,0,2},{1,0,2},{1,0,2},{0,1,2},{0,1,2},{1,0,2}},{{1,0,2},{1,0,2},{0,1,2},{0,1,2},{0,1,2},{1,0,2},{1,0,2},{0,1,2}},
                                     {{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2}},{{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2}},{{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2}},
                                     {{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2}},{{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2}},{{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,1,2}},
                                     {{0,2,1},{0,2,1},{0,2,1},{0,2,1},{0,1,2},{0,1,2},{0,1,2},{0,1,2}},{{0,1,2},{0,1,2},{0,1,2},{0,1,2},{0,2,1},{0,2,1},{0,2,1},{0,2,1}},{{2,1,0},{0,1,2},{0,1,2},{2,1,0},{2,1,0},{2,1,0},{0,1,2},{0,1,2}},
                                     {{0,1,2},{2,1,0},{2,1,0},{0,1,2},{0,1,2},{0,1,2},{2,1,0},{2,1,0}},{{0,1,2},{0,1,2},{1,0,2},{1,0,2},{1,0,2},{0,1,2},{0,1,2},{1,0,2}},{{1,0,2},{1,0,2},{0,1,2},{0,1,2},{0,1,2},{1,0,2},{1,0,2},{0,1,2}}};

/// Cube struct

long long nodes_visited;
struct cube
{
    const static cube solved;

    int prev_move;
    ull edges=0, verts=0;

    // Loading
    static ull translate_edge(int x, int y) { return edgemap[6*x+y]; }
    static ull translate_vert(int x, int y, int z)
    {
        int cx = min(x, min(y,z));
        int cz = max(x, max(y,z));
        int cy = x+y+z-cx-cz;
        int base = vertmap[4*(cx&1)+2*(cy&1)+(cz&1)];
        if (x<y && x<z) return base;
        if (y<z) return base|8;
        return base|16;
    }
    static cube from_input()
    {
        char input[55];
        unsigned translate[256];
        for (int i=0; i<54; i++) scanf("%s", input+i);
        for (int i=0; i<6; i++) translate[(int)input[centers[i]]] = i;
        for (int i=0; i<54; i++) input[i] = translate[(int)input[i]];
        ull edges=0, verts=0;
        for (int i=0; i<12; i++) edges |= translate_edge(input[edgelist[i][0]], input[edgelist[i][1]])<<(5*i);
        for (int i=0; i< 8; i++) verts |= translate_vert(input[vertlist[i][0]], input[vertlist[i][1]], input[vertlist[i][2]])<<(5*i);
        return cube(edges, verts);
    }
    cube(ull edges, ull verts, int pm=-1) : prev_move(pm), edges(edges), verts(verts) {}
    static cube random_cube(int scramble=30, int seed=-1)
    {
        seed += time(NULL);
        printf("Random cube with seed "); cout << seed << '\n';
        srand(seed);
        for (int i=0; i<100; i++) rand();

        ull edges = solved.edges;
        ull verts = solved.verts;
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

    // Move making
    cube make_move(int moveid) const
    {
        ull ecopy = edges, new_edges=0, new_verts=0;
        for (int i=0; i<12; i++)
        {
            ull new_thing = (ecopy&15) | (edgemoveorient[moveid][i][1&(ecopy>>4)]<<4);
            new_edges |= new_thing << (5*edgemovetable[moveid][i]);
            ecopy >>= 5;
        }
        ecopy = verts; // ahh yes edge copy = vertices great thinking idiot
        for (int i=0; i<8; i++)
        {
            ull new_thing = (ecopy&7) | (vertmoveorient[moveid][i][3&(ecopy>>3)]<<3);
            new_verts |= new_thing << (5*vertmovetable[moveid][i]);
            ecopy >>= 5;
        }
        return cube(new_edges, new_verts, moveid);
    }
}
const cube::solved(0x5a928398a418820, 0x398a418820);

/// "Chunks"

template<bool edge, ull mask> ull mask_bits(const cube &c)
{
    if constexpr (edge) return c.edges & mask;
    else return c.verts & mask;
}
ull edge_groups(const cube &c)
{
    ull ret = 0;
    ull ecopy = c.edges;
    for (int i=0; i<12; i++)
    {
        auto loc = (ecopy&15);
        if (loc >= 4 && loc < 8) ret |= 2;
        else ret |= loc&1;
        ret <<= 2;
        ecopy >>= 5;
    }
    return ret;
}
struct chunk
{
    ull (* const mask)(const cube &);
    unordered_map<ull, int> mask_to_id;
    vector<int> distance;
    vector<int> move_transform[18];

    chunk(ull (*m)(const cube &)) : mask(m)
    {
        // setup
        queue<cube> q;
        vector<cube> witness;
        mask_to_id[mask(cube::solved)] = 0;
        witness.push_back(cube::solved);
        distance.push_back(0);
        q.push(cube::solved);

        // bfs
        while (!q.empty())
        {
            cube cur = q.front();
            q.pop();
            for (int i=0; i<18; i++)
            {
                if (cur.prev_move >= 0)
                {
                    if (i%6 == cur.prev_move%6) continue;
                    if ((cur.prev_move-i+30)%6 == 1 && cur.prev_move%6) continue;
                }
                cube next = cur.make_move(i);
                if (mask_to_id.count(mask(next))) continue;
                mask_to_id[mask(next)] = witness.size();
                witness.push_back(next);
                distance.push_back(1 + distance[mask_to_id[mask(cur)]]);
                q.push(next);
            }
        }

        // move table
        for (int i=0; i<18; i++)
        {
            move_transform[i].resize(witness.size());
            for (size_t j=0; j<witness.size(); j++) move_transform[i][j] = mask_to_id[mask(witness[j].make_move(i))];
        }
    }

    void print(void)
    {
        printf("Chunk size: %llu\n", move_transform[0].size());
    }
};
// Sizes: 2048 2187 34650 70
chunk masks[] = {mask_bits<1, 0b0'10000'10000'10000'10000'10000'10000'10000'10000'10000'10000'10000'10000>,
                 mask_bits<0, 0b0'11000'11000'11000'11000'11000'11000'11000'11000>,
                 edge_groups,
                 mask_bits<0, 0b0'00001'00001'00001'00001'00001'00001'00001'00001>};

double DEBUG_1 = timer.clock()();

/// Phase 2
static inline ull wyhash64(ull x)
{
    x ^= x >> 32;
    x *= 0xd6e8feb86659fd93ULL;
    x ^= x >> 32;
    x *= 0xd6e8feb86659fd93ULL;
    x ^= x >> 32;
    return x;
}
struct cube_hash
{
    size_t operator()(cube const& c) const noexcept
    {
        ull h = 0x9e3779b97f4a7c15ULL;
        h ^= wyhash64(c.edges);
        h = wyhash64(h ^ c.verts);
        return h;
    }
};
unordered_map<cube,pair<int,int>,cube_hash> phase_2;

void phase_2_solver(void)
{
    const int move_reversal[] = {12,13,14,15,16,17,6,7,8,9,10,11,0,1,2,3,4,5};
    phase_2.reserve(663552);
    queue<cube> q;
    q.push(cube::solved);
    phase_2.emplace(cube::solved, pair<int,int>{0,-1});
    while (!q.empty())
    {
        const cube cur = q.front();
        auto [dist,_] = phase_2.at(cur);
        ++dist;
        q.pop();
        for (int i=6; i<12; i++) if (i != cur.prev_move)
        {
            const cube next = cur.make_move(i);
            auto [_, inserted] = phase_2.try_emplace(next, pair<int,int>{dist,move_reversal[i]});
            if (inserted) q.push(next);
        }
    }
}

double DEBUG_2 = timer.clock()();

/// "Tables"

struct table
{
    vector<int> distance;
    vector<int> move_transform[18];
    const chunk &a, &b;
    const int N, M;

    void init(const vector<int> * const a_transform, const vector<int> * const b_transform)
    {
        // move table
        assert(INT_MAX / N > M);
        distance.resize(N*M, 0);
        for (int i=0; i<18; i++)
        {
            move_transform[i].resize(N*M);
            for (int j=0; j<N; j++)
                for (int k=0; k<M; k++)
                    move_transform[i][j*M+k] = a_transform[i][j]*M + b_transform[i][k];
        }

        // bfs
        queue<int> q;
        q.push(0);
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            for (int i=0; i<18; i++)
            {
                // apparently move pruning is slower
                int next = move_transform[i][cur];
                if (!next || distance[next]) continue;
                distance[next] = 1 + distance[cur];
                q.push(next);
            }
        }
    }

    int convert(const cube &c) const
    {
        return a.mask_to_id.at(a.mask(c))*M + b.mask_to_id.at(b.mask(c));
    }

    table(const chunk &a, const chunk &b) : a(a), b(b), N(a.move_transform[0].size()), M(b.move_transform[0].size()) { init(a.move_transform, b.move_transform); }
};

// Sizes:  4,478,976  485,100
table tables[] = {{masks[0], masks[1]},
                  {masks[2], masks[3]},
                  {masks[0], masks[3]},
                  {masks[1], masks[3]}};

double DEBUG_3 = timer.clock()();


/// Phase 1

struct phase_1
{
    int heuristic=0, prev_move=-1;
    int state[4];

    phase_1(void) {}
    phase_1(const cube &c)
    {
        for (int i=0; i<4; i++)
            state[i] = tables[i].convert(c);
    }

    phase_1 make_move(int moveid) const
    {
        phase_1 ret;
        for (int i=0; i<4; i++)
            ret.state[i] = tables[i].move_transform[moveid][state[i]];
        ret.prev_move = moveid;
        return ret;
    }

    void calc_heuristic(void)
    {
        for (int i=0; i<4; i++)
            heuristic = max(heuristic, tables[i].distance[state[i]]);
    }
};

cube phase_1_scramble(0,0);
int moves[20];
jmp_buf phase_1_start;
int phase_1_dfs(const phase_1 &cur, const int depth, const int fmax)
{
    nodes_visited++;
    if (!cur.heuristic)
    {
        cube x = phase_1_scramble;
        for (int i=0; i<depth; i++) x = x.make_move(moves[i]);
        auto it = phase_2.find(x);
        if (it != phase_2.end())
        {
            for (int i=0; i<depth; i++) printf("%s", move_names[moves[i]]);
            cube cur = x;
            while (cur != cube::solved)
            {
                int moveid = phase_2.at(cur).second;
                printf("%s", move_names[moveid]);
                cur = cur.make_move(moveid);
            }
            longjmp(phase_1_start, depth + it->second.first);
        }
    }
    if (cur.heuristic + depth > fmax) return -cur.heuristic-depth;

    int ret = INT_MIN;
    for (int i=0; i<18; i++)
    {
        if (cur.prev_move>=0)
        {
            if (i%6 == cur.prev_move%6) continue;
            if ((cur.prev_move-i+30)%6 == 1 && cur.prev_move%6) continue;
        }
        phase_1 next = cur.make_move(i);
        next.calc_heuristic();
        moves[depth] = i;
        ret = max(ret, phase_1_dfs(next, depth+1, fmax));
    }
    return ret;
}
int phase_1_solver(const cube &raw)
{
    phase_1_scramble = raw;
    phase_1 start(raw);
    start.calc_heuristic();
    for (volatile int depth=1; depth<=13; depth=depth+1) // experimental results show a distribution from 8 to 14
    {
        int res = setjmp(phase_1_start);
        if (!res) phase_1_dfs(start, 0, depth);
        else return res;
    }
    puts("failure");
    return 0; // failure????
}

/// Main

const int trials = 100;

struct trial_record
{
    int wincount=0, trials=0;
    long long total_vis=0, min_vis=LLONG_MAX, max_vis=0;
    int total_moves=0, min_moves=INT_MAX, max_moves=0;
    double total_time=0, min_time=INT_MAX, max_time=0;

    void add_trial(int moves, double time)
    {
        ++trials;
        wincount += !!moves;
        if (moves)
        {
            total_moves += moves;
            min_moves = min(min_moves, moves);
            max_moves = max(max_moves, moves);
        }
        total_time += time;
        min_time = min(min_time, time);
        max_time = max(max_time, time);
        total_vis += nodes_visited;
        min_vis = min(min_vis, nodes_visited);
        max_vis = max(max_vis, nodes_visited);
        nodes_visited = 0;
    }

    void print(void)
    {
        putchar('\n');
        printf("Completed %d trials\n", trials);
        printf("Success rate %d/%d = %g%%\n", wincount, trials, (double)wincount/trials*100);
        printf("min/avg/max visited: %lld / %.2f / %lld\n", min_vis, (double)total_vis/trials, max_vis);
        printf("min/avg/max moves: %d / %.2f / %d\n", min_moves, (double)total_moves/wincount, max_moves);
        printf("min/avg/max time: %.2fs / %.2fs / %.2fs\n", min_time, total_time/trials, max_time);
        putchar('\n');
    }
};

void sanity(void)
{
    freopen("single_rotations.txt", "r", stdin);
    const cube UDFBLR[] = {cube::from_input(),cube::from_input(),cube::from_input(),cube::from_input(),cube::from_input(),cube::from_input()};
    const cube UDFBLR_twist[] = {cube::from_input(),cube::from_input(),cube::from_input(),cube::from_input(),cube::from_input(),cube::from_input()};

    for (int t=0; t<6; t++)
    {
        cube test = cube::solved.make_move(t);
        printf("Test %d = %d\n", t, test == UDFBLR[t]);
        assert(test == UDFBLR[t]);
    }
    cube cheat = UDFBLR_twist[0].make_move(12);
    for (int t=0; t<6; t++)
    {
        cube test = cheat.make_move(t);
        printf("Test %d = %d\n", t+6, test == UDFBLR_twist[t]);
        assert(test == UDFBLR_twist[t]);
    }
}

void sanity2(void)
{
    int good=0, bad=0;
    for (auto [key, value] : phase_2)
    {
        phase_1 test(key);
        test.calc_heuristic();
        if (test.heuristic) bad++;
        else good++;
    }
    printf("Phase 2->1 good/bad = %d %d\n", good, bad);
}

int main(void)
{
    printf("init times: %.2fs %.2fs %.2fs\n", DEBUG_1, DEBUG_2, DEBUG_3);
    sanity();

    phase_2_solver();
    printf("Found %llu phase 2 positions\n", phase_2.size());
    sanity2();
    for (int i=0; i<4; i++) masks[i].print();
//    printf("Init time: %.2fs\n", timer.clock()());
    trial_record t1;

    for (int t=0; t<trials; t++)
    {
        cube start = cube::random_cube(30, t);
        timer.clock();
        int moves = phase_1_solver(start);
        double time = timer.clock()();
        t1.add_trial(moves, time);

//        if ((t+1)%5 == 0)
            t1.print();
    }
    return 0;
}
