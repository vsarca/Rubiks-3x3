#include <bits/stdc++.h>
using namespace std;

const unsigned centers[] = {4,22,25,28,31,49};
unsigned translate[256];
const unsigned inception[6] = {0,4,2,5,3,1};

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

struct read_input {} IN;
struct prng_input {} RNG;
struct cube
{
    static cube solved;
    static char input[55];

    unsigned long long edges=0, verts=0;

    // Loading
    static unsigned long long translate_edge(int x, int y) { return edgemap[6*x+y]; }
    static unsigned long long translate_vert(int x, int y, int z)
    {
        int cx = min(x, min(y,z));
        int cz = max(x, max(y,z));
        int cy = x+y+z-cx-cz;
        int base = vertmap[4*(cx&1)+2*(cy&1)+(cz&1)];
        if (x<y && x<z) return base;
        if (y<z) return base|8;
        return base|16;
    }
    cube(read_input IN)
    {
        assert(+input == +this->input);
        for (int i=0; i<54; i++) scanf("%s", input+i);
        for (int i=0; i<6; i++) translate[(int)input[centers[i]]] = inception[i];
        for (int i=0; i<54; i++) input[i] = translate[(int)input[i]];
        for (int i=0; i<12; i++) edges |= translate_edge(input[edgelist[i][0]], input[edgelist[i][1]])<<(5*i);
        for (int i=0; i< 8; i++) verts |= translate_vert(input[vertlist[i][0]], input[vertlist[i][1]], input[vertlist[i][2]])<<(5*i);
    }
    cube(long long edges, long long verts) : edges(edges), verts(verts) {}
    cube(prng_input RNG) : edges(solved.edges), verts(solved.verts)
    {
        auto t = time(NULL);
        printf("Random cube with seed "); cout << t << '\n';
        srand(t);
        for (int i=0; i<30; i++)
        {
            auto [e,v] = make_move(rand()%18);
            edges = e;
            verts = v;
        }
    }

    // Debug
    void print(void)
    {
        printf("%llx %llx\n", edges, verts);
        cout << bitset<64>(edges) << '\n' << bitset<64>(verts) << '\n';
    }
    bool operator==(const cube& other) const
    {
        return edges == other.edges && verts == other.verts;
    }


    // Move making
    cube make_move(int moveid)
    {
        cube ret(0,0);
        unsigned long long ecopy = edges;
        for (int i=0; i<12; i++)
        {
            unsigned long long new_thing = (ecopy&15) | (edgemoveorient[moveid][i][1&(ecopy>>4)]<<4);
            ret.edges |= new_thing << (5*edgemovetable[moveid][i]);
            ecopy >>= 5;
        }
        ecopy = verts; // ahh yes edge copy = vertices great thinking idiot
        for (int i=0; i<8; i++)
        {
            unsigned long long new_thing = (ecopy&7) | (vertmoveorient[moveid][i][3&(ecopy>>3)]<<3);
            ret.verts |= new_thing << (5*vertmovetable[moveid][i]);
            ecopy >>= 5;
        }
        return ret;
    }
}
cube::solved(0x5a928398a418820, 0x398a418820);
char cube::input[55];

/*
Indices
          0  1  2
          3  4  5
          6  7  8
 9 10 11 12 13 14 15 16 17 18 19 20
21 22 23 24 25 26 27 28 29 30 31 32
33 34 35 36 37 38 39 40 41 42 43 44
         45 46 47
         48 49 50
         51 52 53

Solved
      0 0 0
      0 0 0
      0 0 0
4 4 4 2 2 2 5 5 5 3 3 3
4 4 4 2 2 2 5 5 5 3 3 3
4 4 4 2 2 2 5 5 5 3 3 3
      1 1 1
      1 1 1
      1 1 1

Twist
      4 0 5
      0 0 0
      4 0 5
3 4 2 0 2 0 2 5 3 0 3 0
4 4 4 2 2 2 5 5 5 3 3 3
3 4 2 1 2 1 2 5 3 1 3 1
      4 1 5
      1 1 1
      4 1 5

U
      0 0 0
      0 0 0
      0 0 0
2 2 2 5 5 5 3 3 3 4 4 4
4 4 4 2 2 2 5 5 5 3 3 3
4 4 4 2 2 2 5 5 5 3 3 3
      1 1 1
      1 1 1
      1 1 1

D
      0 0 0
      0 0 0
      0 0 0
4 4 4 2 2 2 5 5 5 3 3 3
4 4 4 2 2 2 5 5 5 3 3 3
2 2 2 5 5 5 3 3 3 4 4 4
      1 1 1
      1 1 1
      1 1 1

F
      0 0 0
      0 0 0
      4 4 4
4 4 1 2 2 2 0 5 5 3 3 3
4 4 1 2 2 2 0 5 5 3 3 3
4 4 1 2 2 2 0 5 5 3 3 3
      5 5 5
      1 1 1
      1 1 1

B
      5 5 5
      0 0 0
      0 0 0
0 4 4 2 2 2 5 5 1 3 3 3
0 4 4 2 2 2 5 5 1 3 3 3
0 4 4 2 2 2 5 5 1 3 3 3
      1 1 1
      1 1 1
      4 4 4

L
      3 0 0
      3 0 0
      3 0 0
4 4 4 0 2 2 5 5 5 3 3 1
4 4 4 0 2 2 5 5 5 3 3 1
4 4 4 0 2 2 5 5 5 3 3 1
      2 1 1
      2 1 1
      2 1 1

R
      0 0 2
      0 0 2
      0 0 2
4 4 4 2 2 1 5 5 5 0 3 3
4 4 4 2 2 1 5 5 5 0 3 3
4 4 4 2 2 1 5 5 5 0 3 3
      1 1 3
      1 1 3
      1 1 3

Priorities: Top/bottom, then Front/back, and then Left/right, labelled 1 to 6

Edge list: 7/13, 3/10, 1/19, 5/16, 26/27, 30/29, 32/21, 24/23, 46/37, 50/40, 52/43, 48/34
Vertex list: 8/14/15, 2/18/17, 0/20/9, 6/12/11, 47/38/39, 53/42/41, 51/44/33, 45/36/35
Edges take 1 orientation bit + 4 index bits. Orientation 1 is priority mismatch
Vertices take 2 orientation bits + 3 index bits. Orietation is how far down #1 priority is
*/

int tmp(int x, int y, int z) { return 4*(x&1)+2*(y&1)+(z&1); }
int tmp2(int x, int y) { return x*6+y; }

void table_generation(void)
{
    // Load test rotations
    freopen("single_rotations.txt", "r", stdin);
    const cube UDFBLR[] = {IN,IN,IN,IN,IN,IN};
    const cube UDFBLR_twist[] = {IN,IN,IN,IN,IN,IN};

    // Compute edge stuff for 90 degree clockwise
    for (int t=0; t<6; t++)
    {
        for (int i=0; i<12; i++)
        {
            int ind = 0;
            unsigned long long ecopy = UDFBLR[t].edges;
            for (; ind<12; ind++)
            {
                if ((ecopy&15) == i) break;
                ecopy >>= 5;
            }
            edgemovetable[t][i] = ind;
            edgemoveorient[t][i][0] = ((ecopy>>4)&1);
            edgemoveorient[t][i][1] = !edgemoveorient[t][i][0];
        }
    }

    // Compound edge turns
    for (int q=1; q<3; q++)
    {
        for (int t=0; t<6; t++)
            for (int i=0; i<12; i++)
            {
                edgemovetable[6*q+t][i] = edgemovetable[6*(q-1)+t][edgemovetable[t][i]];
                edgemoveorient[6*q+t][i][0] = edgemoveorient[6*(q-1)+t][edgemovetable[t][i]][edgemoveorient[t][i][0]];
                edgemoveorient[6*q+t][i][1] = !edgemoveorient[6*q+t][i][0];
            }
    }

    // Compute vert stuff for 90 degree clockwisefor (int t=0; t<6; t++)
    for (int t=0; t<6; t++)
    {
        for (int i=0; i<8; i++)
        {
            int ind = 0;
            unsigned long long ecopy = UDFBLR[t].verts;
            unsigned long long fcopy = UDFBLR_twist[t].verts;
            for (; ind<8; ind++)
            {
                if ((ecopy&7) == i) break;
                ecopy >>= 5;
                fcopy >>= 5;
            }
            vertmovetable[t][i] = ind;
            vertmoveorient[t][i][0] = ((ecopy>>3)&3);
            // The other two directions are tricky, which is why we have twist cubes in the sample space
            vertmoveorient[t][i][1] = ((fcopy>>3)&3);
            vertmoveorient[t][i][2] = 3 - vertmoveorient[t][i][0] - vertmoveorient[t][i][1];
        }
    }

    // Compound vert turns
    for (int q=1; q<3; q++)
    {
        for (int t=0; t<6; t++)
            for (int i=0; i<8; i++)
            {
                vertmovetable[6*q+t][i] = vertmovetable[6*(q-1)+t][vertmovetable[t][i]];
                for (int j=0; j<3; j++) vertmoveorient[6*q+t][i][j] = vertmoveorient[6*(q-1)+t][vertmovetable[t][i]][vertmoveorient[t][i][j]];
            }
    }

    // Output
    puts("edgemovetable");
    printf("{"); for (int t=0; t<18; t++) {
        printf(t?",{":"{"); for (int i=0; i<12; i++) printf(i?",%d":"%d", edgemovetable[t][i]); printf("}");
    } puts("}");
    puts("edgemoveorient");
    printf("{"); for (int t=0; t<18; t++) {
        printf(t?",{":"{"); for (int i=0; i<12; i++) printf(i?",{%d,%d}":"{%d,%d}", edgemoveorient[t][i][0], edgemoveorient[t][i][1]); printf("}");
    } puts("}");

    puts("vertmovetable");
    printf("{"); for (int t=0; t<18; t++) {
        printf(t?",{":"{"); for (int i=0; i<8; i++) printf(i?",%d":"%d", vertmovetable[t][i]); printf("}");
    } puts("}");
    puts("vertmoveorient");
    printf("{"); for (int t=0; t<18; t++) {
        printf(t?",{":"{"); for (int i=0; i<8; i++) printf(i?",{%d,%d,%d}":"{%d,%d,%d}", vertmoveorient[t][i][0], vertmoveorient[t][i][1], vertmoveorient[t][i][2]); printf("}");
    } puts("}");
}

int main(void)
{
    cube start(IN);
    start.print();

//	// map generation
//    for (int i=0; i<12; i++) edgemap[tmp2(cube::input[edgelist[i][0]], cube::input[edgelist[i][1]])] = i;
//    for (int i=0; i<12; i++) edgemap[tmp2(cube::input[edgelist[i][1]], cube::input[edgelist[i][0]])] = i|16;
//    for (int i=0; i<8; i++) vertexmap[tmp(cube::input[vertexlist[i][0]], cube::input[vertexlist[i][1]], cube::input[vertexlist[i][2]])] = i;
//    for (int i=0; i<36; i++) printf("%d,",edgemap[i]); putchar('\n');
//    for (int i=0; i<8; i++) printf("%d,",vertexmap[i]); putchar('\n');

    table_generation();

    return 0;
}
