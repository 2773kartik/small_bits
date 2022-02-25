#include<bits/stdc++.h>
#define fio(a,b) for(int i = a; i < b; ++i)
#define vi vector<int>
#define pb(a) push_back(a)

using namespace std;

const int N = 100000;


struct cntr
{
    string name; int skill;
    int id; int status;
};

struct prjc
{
    string name;
    int days, score, bestbefore, roles;
    vector<pair<string, int>> projectskill;
    int goodratio;
};

bool compare(prjc a, prjc b) {
   return (a.goodratio > b.goodratio);
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #else
        //Online submission
    #endif // MACRO
    int day = 0, contributor, project;

    map<string, vector<pair<int, int>>> skills; //map<string, map<name,skill_level>>     skills[c++][anna] = 3

    cin>>contributor>>project;
    //cout<<contributor<<project;
    cntr people[contributor];
    string skill_name; int levels;
    fio(0, contributor) {
        cin>>people[i].name>>people[i].skill;
        people[i].id = i+1;
        for(int j = 0; j < people[i].skill; ++j) {
            cin>>skill_name>>levels;
            skills[skill_name].pb(make_pair(levels, i+1));
        }
    }
    prjc projects[project];
    fio(0, project) {
        cin>>projects[i].name>>projects[i].days>>projects[i].score>>projects[i].bestbefore>>projects[i].roles;
        projects[i].goodratio = projects[i].score/((projects[i].bestbefore-projects[i].days+1)*N);
        for(int j = 0; j < projects[i].roles; ++j) {
            cin>>skill_name>>levels; //levels = level  and skill_name = skill
            projects[i].projectskill.push_back(make_pair(skill_name, levels));
        }
        //cout<<projects[i].name<<" "<<projects[i].score<<" "<<projects[i].goodratio<<"\n";
    }
    // INPUT PORTION OVER
    sort(projects, projects+project, compare);

    
    int done = 0, check = 0; bool turn = 0;
    vector<string> final;
    fio(0, project) {
        vector<string> answer;
        check = 0; int j;
        answer.pb(projects[i].name);
        answer.pb("newl");
        for(j = 0; j < projects[i].roles; ++j) {
            turn = 0;
            for(auto x: skills[projects[i].projectskill[j].first]) {
                if(x.first >= projects[i].projectskill[j].second) {
                    if(people[x.second-1].status==1) continue;
                    else {
                        answer.pb(people[x.second-1].name); turn = 1;
                        people[x.second-1].status = 1;
                        x.first++;
                        break; 
                    }
                }
            }
            if(turn) ++check;
            turn = 0;
        }
        if(check==j) {
            final.insert(final.end(), answer.begin(), answer.end());
            final.pb("newl");
            ++done;
            
        }
        for(int pp = 0; pp < contributor; ++pp) {
            people[pp].status = 0;
        }
    }
    cout<<done<<"\n";
    for(auto y:final) {
        if(y=="newl") cout<<"\n";
        else cout<<y<<" ";
    }
    return 0;
}