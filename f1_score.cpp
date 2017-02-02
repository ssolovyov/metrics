
#include "utils.h"


int SIZE;


double f1_score(unordered_map<int, double> *y_true, unordered_map<int, double> *y_pred, int *ind, int size);

int main(int argc, char* argv[]) {
    
    int *ind;
    unordered_map<int, double> table1, table2;
    
    read_data_csv(string(argv[1]), &table1);
    read_data_csv(string(argv[2]), &table2);
    ind = read_indexes(string(argv[3]));
    
    cout << "answer: " << f1_score(&table1, &table2, ind, SIZE) << endl;
    
    delete ind, table1, table2;
    return 0;
}


double f1_score(unordered_map<int, double> *y_true, unordered_map<int, double> *y_pred, int *ind, int size) {
   
    double tp, fp, fn, recall, precision;
    int idx;
    
    tp = fp = fn = 0;
    
    for(int i = 0; i < size; i++) {
        
        idx = ind[i]; 
        if((*y_pred).count(idx)) {
            if((*y_pred)[idx] == 1 || (*y_pred)[idx] == 0) {
                if((*y_true)[idx] == 1) {
                    if((*y_pred)[idx] == 1) tp++;
                    else fn++;
                } else {
                    if((*y_pred)[idx] == 1) fp++;
                }
            } else {
                cout << "Wrong prediction: " << (*y_pred)[idx] << endl;
                throw "Wrong prediction";
            }
        } else {
                cout << "Index does not exist: " << idx << endl;
                throw  "Index does not exist";
        }
    }
    
    recall = tp / (tp + fn);
    if( tp != 0) {
        precision = tp / (tp + fp);
    } else {
        precision = 1;
    }
    
    return 2 * recall * precision / (recall + precision);
}
