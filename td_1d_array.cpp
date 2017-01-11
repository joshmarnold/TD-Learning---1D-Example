// 1D TD-learning example
// included output to see
// how algorithm is working
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <cmath>
#include <random>
using namespace std;

int main(int argc, const char * argv[]) {
    
    const int NUM = 10;
    
    srand(5);
    
    double gamma=0.5;
    
    // generate reward array and nstates
    double reward[NUM] = {0};
    double nstates[NUM] = {0};
    
    // designate goal state (position 1 in this case)
    int goal = 1;
    
    reward[goal] = 1;
    
    int pos=0;
    int r;  // used to store reward
    double current_value;
    
    // Break learning up into episodes
    for(int i = 0;i<50;i++)
    {
        double td_error;
        
        // generate random starting position
        pos = rand() % NUM;
        
        // Each epidose will run 100x until goal
        // is found. if goal is not found, start over
        for(int j =0;j<100;j++)
        {
            int setwi = 9;
            int setp = 3;
            cout << setw(7) << left << i << ": ";
            for(int i=0;i<NUM;i++) {
                if(i == pos)
                    if(i == goal)
                        cout <<  setw(setwi) << left << setprecision(setp) << "Goal" << " ";
                    else
                        cout <<  setw(setwi) << left << setprecision(setp) << "Here" << " ";
                    else
                        cout <<  setw(setwi) << left << setprecision(setp) << nstates[i] << " ";
            }
            cout << "|  starting pos: " << pos << endl;
            
            r = reward[pos];
            current_value = nstates[pos];
            
            if(pos == goal) { /* if current position = goalstate */
                
                int previous = pos;
                int previous_val = current_value;
                td_error = r - previous_val;
                
                nstates[previous] += td_error;
                break;
            }
            
            
            // The next possible states are to the
            // immediate left and right
            // Get the values of these neighboring states
            double left_val = 0;
            double right_val = 0;
            if(pos==0)  /* going left */
                left_val = nstates[NUM-1]; // position needs to wrap around to end
            else
                left_val = nstates[pos-1];
            if(pos==NUM-1)  /* going right */
                right_val = nstates[0]; // position needs to wrap around to beginning
            else
                right_val = nstates[pos+1];
            
            
            td_error = 0;
            if(left_val > right_val) {
                if(pos==0) { /* going left */
                    td_error = (r + gamma*nstates[NUM-1]) - current_value;
                    nstates[pos] += td_error;
                    pos = NUM-1;
                } else {
                    td_error = (r + gamma*nstates[pos-1]) - current_value;
                    nstates[pos] += td_error;
                    pos-=1;
                }
            } else { /* going right */
                if(pos==NUM-1) { 
                    td_error = (r + gamma*nstates[0]) - current_value;
                    nstates[pos] += td_error;
                    pos = 0;
                } else {
                    td_error = (r + gamma*nstates[pos+1]) - current_value;
                    nstates[pos] += td_error;
                    pos+=1;
                }
            }
        }
    }
    
    return 0;
}
