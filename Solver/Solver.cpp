#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <fstream>

using namespace std;

typedef vector<int> cubestate;

 ofstream solve("solve.txt");

int applicableMoves[] = {0, 262143, 259263, 74943, 74898};
int moves=0;

int affectedCubies[][8] = {
    { 0, 1, 2, 3, 0, 1, 2, 3 },   // U
    { 4, 7, 6, 5, 4, 5, 6, 7 },   // D
    { 0, 9, 4, 8, 0, 3, 5, 4 },   // F
    { 2, 10, 6, 11, 2, 1, 7, 6 }, // B
    { 3, 11, 7, 9, 3, 2, 6, 5 },  // L
    { 1, 8, 5, 10, 1, 0, 4, 7 },  // R
};

cubestate applyMove(int move, cubestate state)
{
    int turns = move % 3 + 1;
    int face = move / 3;

    while (turns--) {
        cubestate oldState = state;

        for (int i = 0; i < 8; i++) {
            int isCorner = i > 3;
            int target = affectedCubies[face][i] + isCorner * 12;
            int killer = affectedCubies[face][(i & 3) == 3 ? i - 3 : i + 1] + isCorner * 12;
            int orientationDelta = (i < 4) ? (face > 1 && face < 4) : (face < 2) ? 0 : 2 - (i & 1);

            state[target] = oldState[killer];
            state[target + 20] = oldState[killer + 20] + orientationDelta;

            if (!turns)
                state[target + 20] %= 2 + isCorner;
        }
    }
    return state;
}

int inverse(int move)
{
    return move + 2 - 2 * (move % 3);
}

int phase;

cubestate id(cubestate state)
{

    //--- Phase 1: Edge orientations.
    if (phase < 2)
        return cubestate(state.begin() + 20, state.begin() + 32);

    //-- Phase 2: Corner orientations, E slice edges.
    if (phase < 3) {
        cubestate result(state.begin() + 31, state.begin() + 40);
        for (int e = 0; e < 12; e++)
            result[0] |= (state[e] / 8) << e;
        return result;
    }

    //--- Phase 3: Edge slices M and S, corner tetrads, overall parity.
    if (phase < 4) {
        cubestate result(3);
        for (int e = 0; e < 12; e++)
            result[0] |= ((state[e] > 7) ? 2 : (state[e] & 1)) << (2 * e);
        for (int c = 0; c < 8; c++)
            result[1] |= ((state[c + 12] - 12) & 5) << (3 * c);
        for (int i = 12; i < 20; i++)
            for (int j = i + 1; j < 20; j++)
                result[2] ^= state[i] > state[j];
        return result;
    }

    //--- Phase 4: The rest.
    return state;
}

//int argc, char** argv

int main(int argc, char** argv)
{
	
//	string argv[] = { "LB" , "LB" ,  "DR" , "RB" , "UF" , "UR" , "LF" , "LU" , "RF" , "DB" , "DL" , "DF" , "BU" , "LFU" , "RUF" , "RBU" , "LUB" , "LBD" , "RDB" , "RFD" , "LDF" };

    //--- Define the goal.
    string goal[] ={ "UF", "UR", "UB", "UL", "DF", "DR", "DB", "DL", "FR", "FL", "BR", "BL",
        "UFR", "URB", "UBL", "ULF", "DRF", "DFL", "DLB", "DBR" };

    //--- Prepare current (start) and goal state.
    cubestate currentState(40), goalState(40);
    for (int i = 0; i < 20; i++) {

        //--- Goal state.
        goalState[i] = i;

        //--- Current (start) state.
        string cubie = argv[i + 1];
        while ((currentState[i] = find(goal, goal + 20, cubie) - goal) == 20) {
            cubie = cubie.substr(1) + cubie[0];
            currentState[i + 20]++;
        }
    }

    //--- Dance the funky Thistlethwaite...
    while (++phase < 5) {

        //--- Compute ids for current and goal state, skip phase if equal.
        cubestate currentId = id(currentState), goalId = id(goalState);
        if (currentId == goalId)
            continue;

        //--- Initialize the BFS queue.
        queue<cubestate> q;
        q.push(currentState);
        q.push(goalState);

        //--- Initialize the BFS tables.
        map<cubestate, cubestate> predecessor;
        map<cubestate, int> direction, lastMove;
        direction[currentId] = 1;
        direction[goalId] = 2;

        //--- Dance the funky bidirectional BFS...
        while (1) {

            //--- Get state from queue, compute its ID and get its direction.
            cubestate oldState = q.front();
            q.pop();
            cubestate oldId = id(oldState);
            int& oldDir = direction[oldId];

            //--- Apply all applicable moves to it and handle the new state.
            for (int move = 0; move < 18; move++) {
                if (applicableMoves[phase] & (1 << move)) {

                    //--- Apply the move.
                    cubestate newState = applyMove(move, oldState);
                    cubestate newId = id(newState);
                    int& newDir = direction[newId];

                    //--- Have we seen this state (id) from the other direction already?
                    //--- I.e. have we found a connection?
                    if (newDir && newDir != oldDir) {

                        //--- Make oldId represent the forwards and newId the backwards search state.
                        if (oldDir > 1) {
                            swap(newId, oldId);
                            move = inverse(move);
                        }

                        //--- Reconstruct the connecting algorithm.
                        cubestate algorithm(1, move);
                        while (oldId != currentId) {
                            algorithm.insert(algorithm.begin(), lastMove[oldId]);
                            oldId = predecessor[oldId];
                        }
                        while (newId != goalId) {
                            algorithm.push_back(inverse(lastMove[newId]));
                            newId = predecessor[newId];
                        }

                        //--- Print and apply the algorithm.
                        for (int i = 0; i < (int)algorithm.size(); i++) {
                        	
                        	if((algorithm[i] % 3 + 1 )==3){
                        		
                        		cout <<  "UDFBLR" [algorithm[i] / 3];
                        		solve << "UDFBLR" [algorithm[i] / 3];
                        		moves++;
							}
							
							else if((algorithm[i] % 3 + 1 )==1){
								 cout <<  "udfblr" [algorithm[i] / 3] ;
								 solve << "udfblr" [algorithm[i] / 3] ;
								 moves++;
							}
                        	
                        	else{
                        		cout <<  "UDFBLR" [algorithm[i] / 3] << algorithm[i] % 3 + 1;
                        		solve << "UDFBLR" [algorithm[i] / 3] << algorithm[i] % 3 + 1;
                        		moves++;
							}
                        	
                            
                            currentState = applyMove(algorithm[i], currentState);
                        }

                        //--- Jump to the next phase.
                        goto nextPhase;
                    }

                    //--- If we've never seen this state (id) before, visit it.
                    if (!newDir) {
                        q.push(newState);
                        newDir = oldDir;
                        lastMove[newId] = move;
                        predecessor[newId] = oldId;
                    }
                }
            }
        }
    nextPhase:;
    }
    
    solve.close();
    cout<< "\n Total number of moves "<< ":" << moves ;
    
}