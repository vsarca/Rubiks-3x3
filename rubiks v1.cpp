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

const unsigned centers[] = {4,22,25,28,31,49};
const unsigned inception[6] = {0,4,2,5,3,1};

const unsigned edgelist[][2] = {{7,13}, {5,16}, {1,19}, {3,10}, {26,27}, {30,29}, {32,21}, {24,23}, {46,37}, {50,40}, {52,43}, {48,34}};
const unsigned vertlist[][3] = {{8,14,15},{2,18,17}, {0,20,9}, {6,12,11}, {47,38,39}, {53,42,41}, {51,44,33}, {45,36,35}};

unsigned edgemap[36] = {0,0,0,2,3,1,0,0,8,10,11,9,16,24,0,8,7,4,18,26,24,0,6,5,19,27,23,22,0,6,17,25,20,21,22,0};
unsigned vertmap[8] = {3,0,2,1,7,4,6,5};

// [move, index] = index, UDFBLR order
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

/// Cube struct

long long nodes_visited;
struct cube
{
    static cube solved;

    int score; // TODO: update or remove
    short move_count, prev_move;
    ull edges=0, verts=0;



    // Move making
    template<int moveid> cube make_move(void) const
    {
        constexpr bool edge_preserve[] = {1,1,0,0,1,1, 1,1,1,1,1,1, 1,1,0,0,1,1};
        ull ecopy = edges, new_edges=0, new_verts=0;
        if constexpr (!edge_preserve[moveid])
        {
            for (int i=0; i<12; i++)
            {
                ull new_thing = (ecopy&15) | (edgemoveorient[moveid][i][1&(ecopy>>4)]<<4);
                new_edges |= new_thing << (5*edgemovetable[moveid][i]);
                ecopy >>= 5;
            }
        }
        else
        {
            for (int i=0; i<12; i++)
            {
                new_edges |= (ecopy&31) << (5*edgemovetable[moveid][i]);
                ecopy >>= 5;
            }
        }
        ecopy = verts; // ahh yes edge copy = vertices great thinking idiot
        if constexpr (moveid<6 || moveid>=12)
        {
            for (int i=0; i<8; i++)
            {
                ull new_thing = (ecopy&7) | (vertmoveorient[moveid][i][3&(ecopy>>3)]<<3);
                new_verts |= new_thing << (5*vertmovetable[moveid][i]);
                ecopy >>= 5;
            }
        }
        else
        {
            for (int i=0; i<8; i++)
            {
                new_verts |= (ecopy&31) << (5*vertmovetable[moveid][i]);
                ecopy >>= 5;
            }
        }
        return cube(new_edges, new_verts, move_count+1, moveid);
    }


    using move_func = cube (cube::*)(void) const;
    static constexpr move_func move_table[18] = {cube::make_move<0>,
                                                 cube::make_move<1>,
                                                 cube::make_move<2>,
                                                 cube::make_move<3>,
                                                 cube::make_move<4>,
                                                 cube::make_move<5>,
                                                 cube::make_move<6>,
                                                 cube::make_move<7>,
                                                 cube::make_move<8>,
                                                 cube::make_move<9>,
                                                 cube::make_move<10>,
                                                 cube::make_move<11>,
                                                 cube::make_move<12>,
                                                 cube::make_move<13>,
                                                 cube::make_move<14>,
                                                 cube::make_move<15>,
                                                 cube::make_move<16>,
                                                 cube::make_move<17>};

    // Loading
    static ull translate_edge(int x, int y) { return edgemap[6*x+y]; }
    static ull translate_vert(int x, int y, int z)
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
        ull edges=0, verts=0;
        for (int i=0; i<12; i++) edges |= translate_edge(input[edgelist[i][0]], input[edgelist[i][1]])<<(5*i);
        for (int i=0; i< 8; i++) verts |= translate_vert(input[vertlist[i][0]], input[vertlist[i][1]], input[vertlist[i][2]])<<(5*i);
        return cube(edges, verts);
    }
    cube(ull edges, ull verts, int mc=0, int pm=-1) : score(0), move_count(mc), prev_move(pm), edges(edges), verts(verts) {}
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
            cube next = (cube(edges, verts).*move_table[rand()%18])();
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
}
cube::solved(0x5a928398a418820, 0x398a418820);

/// "Chunks"

template<bool edge, ull mask, ull xormask=0> ull mask_bits(const cube &c)
{
    if constexpr (edge) return (c.edges^xormask) & mask;
    else return (c.verts^xormask) & mask;
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
                cube next = (cur.*cube::move_table[i])();
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
            for (size_t j=0; j<witness.size(); j++) move_transform[i][j] = mask_to_id[mask((witness[j].*cube::move_table[i])())];
        }
    }

    void print(void)
    {
        printf("Chunk size: %llu\n", move_transform[0].size());
    }
};
// Sizes: 2048 2187 34650 14
chunk masks[] = {mask_bits<1, 0b0'10000'10000'10000'10000'10000'10000'10000'10000'10000'10000'10000'10000>,
                 mask_bits<0, 0b0'11000'11000'11000'11000'11000'11000'11000'11000>,
                 edge_groups,
                 mask_bits<0, 0b0'00001'00001'00001'00001'00001'00001'00001'00001, 0b0'00001'00001'00001'00001>};


/// Phase 2


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


/// Phase 1 simplified cube state

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

int phase_1_dfs(const phase_1 &cur, const int depth, const int fmax)
{
    nodes_visited++;
    if (!cur.heuristic) return depth;
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
        ret = max(ret, phase_1_dfs(next, depth+1, fmax));
    }
    return ret;
}
int phase_1_solver(const cube &raw)
{
    phase_1 start(raw);
    start.calc_heuristic();
    for (int depth=8; depth<=14; depth++) // experimental results show a distribution from 8 to 14
//    for (int depth=start.heuristic; depth<=20; depth++)
    {
        int res = phase_1_dfs(start, 0, depth);
        if (res >= 0) return res;
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
        printf("Completed %d trials\n", trials);
        printf("Success rate %d/%d = %g%%\n", wincount, trials, (double)wincount/trials*100);
        printf("min/avg/max visited: %lld / %.2f / %lld\n", min_vis, (double)total_vis/wincount, max_vis);
        printf("min/avg/max moves: %d / %.2f / %d\n", min_moves, (double)total_moves/wincount, max_moves);
        printf("min/avg/max time: %.2fs / %.2fs / %.2fs\n", min_time, total_time/trials, max_time);
        putchar('\n');
    }
};

int main(void)
{
    for (int i=0; i<4; i++) masks[i].print();
    printf("Init time: %.2fs\n", timer.clock()());
    trial_record t1;

    for (int t=0; t<trials; t++)
    {
        cube start = cube::random_cube(30, t);
        timer.clock();
        int moves = phase_1_solver(start);
        double time = timer.clock()();
        t1.add_trial(moves, time);

        if ((t+1)%5 == 0) t1.print();
    }
    return 0;
}
