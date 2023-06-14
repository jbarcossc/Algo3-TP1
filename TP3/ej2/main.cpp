#include <iostream>
#include <vector>
#include ""


using namespace std;

int n, m;
vector<vector<bool>> amistad; //matriz de n x n
vector<bool> voto;



int main() {
    //intput
    while (true){
        cin >> n; cin >> m;
        if (n==0 && m==0) break;
        voto.assign(n,false);
        amistad.assign(n,voto);
        for (int i = 0; i < n; ++i) {
            bool v; cin >> v;
            voto[i]=v;
        }
        while (m--){
            int v,w;
            cin >> v; cin >> w;
            amistad[v][w]=true;
            amistad[w][v]=true;
        }

        //llamar al algoritmo//

        // output
        cout << res << endl;
    }



    return 0;
}