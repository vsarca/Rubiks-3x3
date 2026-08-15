#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

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

typedef unsigned long long ull;

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
    cube(){}
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
    void print(void) const
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

template<bool edge, unsigned offs, unsigned width, unsigned cnt> unsigned mask_bits(const cube &c)
{
    const ull &data = edge ? c.edges : c.verts;
    unsigned ret = 0;
    for (unsigned i=0; i<cnt; i++) ret = (ret<<(width)) | (((1<<width)-1) & (data>>(offs+5*i)));
    return ret;
}
unsigned edge_groups(const cube &c)
{
    unsigned ret = 0;
    for (int i=0; i<12; i++)
    {
        ret *= 3;
        const auto loc = ((c.edges >> (5*i)) & 15);
        if ((loc&12) == 4) ret += 2;
        else ret += loc&1;
    }
    return ret;
}
struct chunk
{
    unsigned (* const mask)(const cube &);
    int *mask_to_id;
    vector<int> distance;
    vector<int> move_transform[18];

    chunk(unsigned mapsize, unsigned (*m)(const cube &)) : mask(m)
    {
        // setup
        mask_to_id = (int*)malloc(sizeof(int) * mapsize);
        memset(mask_to_id, -1, sizeof(int) * mapsize);
        queue<cube> q;
        vector<cube> witness;
//        if (mask(cube::solved) >= mapsize) printf("Over %d >= %d\n", mask(cube::solved), mapsize);
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
                const auto masked = mask(next);
//                if (masked >= mapsize) printf("Over2 %d >= %d\n", masked, mapsize);
                if (mask_to_id[masked] >= 0) continue;
                mask_to_id[masked] = witness.size();
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
chunk masks[] = {{4096, mask_bits<1, 4, 1, 12>},
                 {65536, mask_bits<0, 3, 2, 8>},
                 {531441, edge_groups},
                 {256, mask_bits<0, 0, 1, 8>}};

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
gp_hash_table<cube,pair<int,int>,cube_hash> old_phase_2;
unordered_map<int,cube> phase_2_debug;

int phase_2_trans[4][65536];
int phase_2_lens[4]; // 96 24 24 24
pair<int,int> phase_2[1327104];
//unordered_map<int,pair<int,int>> phase_2;
unsigned phase_2_mask(const cube &c)
{
    unsigned piece[4] = {0};
    for (int i=0; i<8; i++) piece[0] = (piece[0]<<2) | ((c.verts >> (1+5*i)) & 3);
    for (int i : {0,2,8,10}) piece[1] = (piece[1]<<4) | ((c.edges >> (5*i)) & 15);
    for (int i=4; i<8; i++) piece[2] = (piece[2]<<4) | ((c.edges >> (5*i)) & 15);
    for (int i : {1,3,9,11}) piece[3] = (piece[3]<<4) | ((c.edges >> (5*i)) & 15);
    for (int t=0; t<4; t++) assert(piece[t] < 65536);
    for (int t=0; t<4; t++) if (phase_2_trans[t][piece[t]] == -1) phase_2_trans[t][piece[t]] = phase_2_lens[t]++;
    unsigned ret = 0;
    for (int t=0; t<4; t++) ret = ret*24 + phase_2_trans[t][piece[t]];
    return ret;
}
void phase_2_solver(void)
{
    memset(phase_2_trans[0], -1, sizeof(phase_2_trans));
    int sanity_total = 0;
    const int move_reversal[] = {12,13,14,15,16,17,6,7,8,9,10,11,0,1,2,3,4,5};
    queue<cube> q;
    q.push(cube::solved);
    phase_2[phase_2_mask(cube::solved)] = {0,-1};
    phase_2_debug[phase_2_mask(cube::solved)] = cube::solved;
    sanity_total++;
    old_phase_2.insert({cube::solved, pair<int,int>{0,-1}});
    while (!q.empty())
    {
        const cube cur = q.front();

        const auto it = old_phase_2.find(cur);
        auto [real_dist,_] = it->second;

        auto [dist,_] = phase_2[phase_2_mask(cur)];
        ++dist;
        q.pop();
        for (int i=6; i<12; i++) if (i != cur.prev_move)
        {
            const cube next = cur.make_move(i);

            auto [_, inserted] = old_phase_2.insert({next, pair<int,int>{dist,move_reversal[i]}});
            if (inserted)
            {
                q.push(next);

                const unsigned masked = phase_2_mask(next);
                if (masked > 1327104) assert(0 + 0 + 0);
//                printf("%d %d %d %d\n", phase_2_lens[0], phase_2_lens[1], phase_2_lens[2], phase_2_lens[3]);
                if (phase_2[masked] != pair<int,int>{0,0})
                {
//                    puts("Well shit, these comapre equal");
//                    next.print();
//                    phase_2_debug[masked].print();
                }
                phase_2[masked] = {dist,move_reversal[i]};
                phase_2_debug[masked] = next;
                sanity_total++;
                q.push(next);
            }
        }
    }
    printf("uhhh %d %d %d %d\n", phase_2_lens[0], phase_2_lens[1], phase_2_lens[2], phase_2_lens[3], sanity_total);
}

/// "Tables"

typedef pair<int,int> table_type;

struct table
{
    int *distance;
    const chunk &a, &b;
    const int N, M;

    void init(const vector<int> * const a_transform, const vector<int> * const b_transform)
    {
        // setup
        assert(INT_MAX / N > M);
        distance = (int*)calloc(N*M, sizeof(int));
        queue<pair<int,int>> q;
        q.push({0,0});

        // bfs
        while (!q.empty())
        {
            auto [j,k] = q.front();
            q.pop();
            for (int i=0; i<18; i++)
            {
                // apparently move pruning is slower
                int nj = a_transform[i][j], nk = b_transform[i][k];
                int next = nj*M + nk;
                if (!next || distance[next]) continue;
                distance[next] = 1 + distance[j*M+k];
                q.push({nj,nk});
            }
        }
    }

    inline table_type convert(const cube &c) const
    {
        return {a.mask_to_id[a.mask(c)], b.mask_to_id[b.mask(c)]};
    }

    inline table_type move_transform(int moveid, const table_type &cur)
    {
        return {a.move_transform[moveid][cur.first], b.move_transform[moveid][cur.second]};
    }
    inline int get_distance(const table_type &cur)
    {
        return distance[cur.first*M + cur.second];
    }

    table(const chunk &a, const chunk &b) : a(a), b(b), N(a.move_transform[0].size()), M(b.move_transform[0].size()) { init(a.move_transform, b.move_transform); }
};

#define NUM_TABLES 4
table tables[] = {{masks[0], masks[1]},
                  {masks[2], masks[3]},
                  {masks[0], masks[3]},
                  {masks[1], masks[3]}};

///// "Tables"
//
//typedef int table_type;
//
//struct table
//{
//    const chunk &a;
//
//    inline table_type convert(const cube &c) const
//    {
//        const auto it = a.mask_to_id.find(a.mask(c));
//        return it->second;
//    }
//
//    inline table_type move_transform(int moveid, const table_type &cur)
//    {
//        return a.move_transform[moveid][cur];
//    }
//    inline int get_distance(const table_type &cur)
//    {
//        return a.distance[cur];
//    }
//
//    table(const chunk &a) : a(a) {}
//};
//
//#define NUM_TABLES 4
//table tables[] = {masks[0], masks[1], masks[2], masks[3]};


double DEBUG_2 = timer.clock()();


/// Phase 1

struct phase_1
{
    int heuristic=0, prev_move=-1;
    table_type state[NUM_TABLES];

    phase_1(void) {}
    phase_1(const cube &c)
    {
        for (int i=0; i<NUM_TABLES; i++)
            state[i] = tables[i].convert(c);
    }

    phase_1 make_move(int moveid) const
    {
        phase_1 ret;
        for (int i=0; i<NUM_TABLES; i++)
            ret.state[i] = tables[i].move_transform(moveid, state[i]);
        ret.prev_move = moveid;
        return ret;
    }

    void calc_heuristic(void)
    {
        for (int i=0; i<NUM_TABLES; i++)
            heuristic = max(heuristic, tables[i].get_distance(state[i]));
    }
};

cube phase_1_scramble(0,0);
//int moves[20];
//jmp_buf phase_1_start;
//int phase_1_dfs(const phase_1 &cur, const int depth, const int fmax)
//{
//    nodes_visited++;
//    if (!cur.heuristic)
//    {
//        cube x = phase_1_scramble;
//        for (int i=0; i<depth; i++) x = x.make_move(moves[i]);
//        const auto [cost,moveid] = phase_2[phase_2_mask(x)];
//        if (cost || moveid)
//        {
//            for (int i=0; i<depth; i++) printf("%s", move_names[moves[i]]);
//            cube cur = x;
//            while (cur != cube::solved)
//            {
//                const auto [_,moveid] = phase_2[phase_2_mask(cur)];
//                printf("%s", move_names[moveid]);
//                cur = cur.make_move(moveid);
//            }
//            longjmp(phase_1_start, depth + cost);
//        }
//    }
//    if (cur.heuristic + depth > fmax) return -cur.heuristic-depth;
//
//    int ret = INT_MIN;
//    for (int i=0; i<18; i++)
//    {
//        if (cur.prev_move>=0)
//        {
//            if (i%6 == cur.prev_move%6) continue;
//            if ((cur.prev_move-i+30)%6 == 1 && cur.prev_move%6) continue;
//        }
//        phase_1 next = cur.make_move(i);
//        next.calc_heuristic();
//        moves[depth] = i;
//        ret = max(ret, phase_1_dfs(next, depth+1, fmax));
//    }
//    return ret;
//}

int phase_1_flat_dfs(const phase_1 &start, const int fmax)
{
    int moves[20];
    phase_1 states[20];
    int depth = 0;

    states[0] = start;
    moves[0] = -1;
    while (depth >= 0)
    {
        nodes_visited++;
        const phase_1 &cur = states[depth];
        if (!cur.heuristic)
        {
            cube x = phase_1_scramble;
            for (int i=0; i<depth; i++) x = x.make_move(moves[i]);
            const auto [cost,moveid] = phase_2[phase_2_mask(x)];
            if (cost || moveid)
            {
                for (int i=0; i<depth; i++) printf("%s", move_names[moves[i]]);
                cube cur = x;
                while (cur != cube::solved)
                {
                    const auto [_,moveid] = phase_2[phase_2_mask(cur)];
                    printf("%s", move_names[moveid]);
                    cur = cur.make_move(moveid);
                }
                return depth + cost;
            }
        }
        int &i = moves[depth];
        if (cur.heuristic + depth > fmax) --depth;
        else if (++i == 18) --depth;
        else
        {
            if (cur.prev_move >= 0)
            {
                if (i%6 == cur.prev_move%6) continue;
                if ((cur.prev_move-i+30)%6 == 1 && cur.prev_move%6) continue;
            }
            states[++depth] = cur.make_move(i);
            states[depth].calc_heuristic();
            moves[depth] = -1;
        }
    }
    return 0;
}

int phase_1_solver(const cube &raw)
{
    phase_1_scramble = raw;
    phase_1 start(raw);
    start.calc_heuristic();
    for (volatile int depth=1; depth<=13; depth=depth+1) // experimental results show a distribution from 8 to 14
    {
//        int res = setjmp(phase_1_start);
//        if (!res) phase_1_dfs(start, 0, depth);
//        else return res;
        int res = phase_1_flat_dfs(start, depth);
        if (res) return res;
    }
    puts("failure");
    return 0; // failure????
}

/// Main

int main(void)
{
    phase_2_solver();
    double DEBUG_3 = timer.clock()();
    printf("init times: %.2fs %.2fs %.2fs\n", DEBUG_1, DEBUG_2, DEBUG_3);
    cube start = cube::from_input();
    phase_1_solver(start);
    return 0;
}
