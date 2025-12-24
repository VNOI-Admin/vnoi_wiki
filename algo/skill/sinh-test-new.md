---
title: Kỹ thuật sinh test, tự kiểm tra code
description: 
published: true
date: 2025-12-20T11:39:36.633Z
tags: 
editor: markdown
dateCreated: 2025-12-17T14:54:06.267Z
---

# Kỹ thuật sinh test, tự kiểm tra code

**Người viết:**

- Nguyễn Quang Minh - Michigan State University.

**Reviewer:**

- Lê Minh Hoàng - Trường Đại học Khoa học Tự nhiên, ĐHQG-HCM.
- Võ Đức Đoàn - THPT Chuyên Nguyễn Tất Thành, Quảng Ngãi.
- Nguyễn Tiến Mạnh - Đại học Bách khoa Hà Nội.
- Nguyễn Tấn Minh - Trường Đại học Khoa học Tự nhiên, ĐHQG-HCM.

## Giới thiệu

Khi làm bài, mình chắc hẳn ai trong chúng ta cũng thích những việc như nghĩ thuật toán, biến thuật toán mà mình vừa nghĩ ra thành hiện thực (code). Tuy nhiên, một việc cũng quan trọng không kém, thậm chí là quan trọng hơn nhiều trong những kì thi offline (thí sinh chỉ được nộp đúng $1$ lần khi hết giờ, chẳng hạn như VOI), đó chính là sinh test. 

Bài viết này sẽ giúp các bạn biết được những bước cơ bản của việc sinh test.

## Vì sao lại cần sinh test

Khi đi thi một kì thi offline, các bạn không thể tránh được những sai sót trong lúc làm bài. Một vài test được đưa ra trong đề bài hay do bạn tự nghĩ ra chưa chắc đã có thể giúp bản thân phát hiện ra được tất cả những lỗi sai này. Việc sinh test có thể giúp bạn phát hiện ra những lỗi chính trong code của mình, và từ đó đảm bảo một số điểm tốt. 

Việc sinh test còn có thể giúp các bạn rất nhiều trong những kì thi online. Khi thi những kì thi này, tuy biết được điểm số bài làm của mình, nhưng các bạn cũng không hề biết được test sai, lý do sai, v.v. Việc sinh test khi đó là vô cùng cấp thiết. 

Một tác dụng khác của sinh test là kiểm tra thời gian chạy của code với trường hợp xấu nhất. Với việc sinh test, bạn không chỉ biết đuợc thời gian chạy của code, mà cũng có thể đo lường thời gian chạy của một số đoạn code để có thể tập trung vào cải tiến những phần code chiếm phần lớn thời gian, không gian cho phép.

Thoạt nhìn thì có vẻ việc sinh test khá tốn thời gian. Tuy nhiên, khi đã quen với việc sinh test thì việc sinh test sẽ chỉ mất $5-10$ phút - một cái giá quá hời với những lợi ích mà việc này mang lại.

## Trình chấm và những thành phần thường thấy

**Lưu ý**:
- Trình chấm được nêu ra trong bài viết này chạy trên Windows. Với những hệ điều hành khác, một số câu lệnh để chạy các file sẽ cần thay đổi.
- Các dấu ``*`` trong file input / output chỉ tên bài. Chẳng hạn như khi tên bài là `ship` thì tên file input sẽ là `ship.inp`. 

Khái niệm:
- "Sinh test": việc tạo ra những bộ input ngẫu nhiên dựa vào các điều kiện mong muốn của bạn.

Ta có một số phần chính của một trình chấm:
### Code "trâu"
Là code đơn giản nhất có thể và không quan trọng độ phức tạp mà có đáp án đúng hoặc thỏa mãn điều kiện đề bài. Khi đi thi bất kì một cuộc thi nào, code "trâu" nên là việc bạn làm đầu tiên. Thậm chí trong những kì thi online, sẽ có $1 - 2$ subtask đầu để các bạn có thể kiểm tra ngay code trâu cũng như việc bạn đã hiểu đề chưa (cũng như kiếm một chút điểm để có thể tự tin hơn). Ta quy ước code "trâu" có input là `*.inp` và output là `*.ans`.

### Code "chuẩn"
Là code hiện tại mà các bạn muốn kiểm tra. Ta quy ước code "chuẩn" có input là `*.inp` và output là `*.out`.

### Code "Sinh test"
Chương trình này sẽ làm những việc sau:
- Tạo ra input (các bạn có thể sử dụng `mt19937` - hàm random phổ biến nhất hiện tại), và đưa vào trong file `*.inp`.
- Chạy code "trâu" và code "chuẩn" để có được file `*.out` và `*.ans`.
- Kiểm tra xem file `*.out` có thỏa mãn điều kiện đề bài không (thường là kiểm tra xem file `*.out` và `*.ans` giống nhau không)
- Nếu file `*.out` không thỏa mãn, dừng code ngay lập tức để có được test sai.

Trình chấm là bộ chương trình giúp các bạn "sinh test", và bao gồm code "trâu", code "chuẩn", và code "sinh test".

## Sử dụng các hàm random để sinh test

Trong C++ có một số thư viện / hàm giúp chúng ta tạo ra các số random như $\texttt{rand}()$ hay $\texttt{mt19937}$. Mình khuyên các bạn sử dụng thư viện $\texttt{mt19937}$ để có thể sinh những số lớn.

Có $2$ cách chính để sử dụng $\texttt{mt19937}$ trong sinh test:

```cpp=
// Trong code gen để debug, các bạn có thể giữ nguyên seed
// để đảm bảo lần nào generator cũng generate ra những test giống nhau.
// Như vậy, các bạn đảm bảo rằng code của mình thỏa mãn tất cả những test từng sai
mt19937 rng(7405);
 
// Còn nếu các bạn muổn random hoàn toàn (để check lại
// lần cuối chẳng hạn) có thể dùng
mt19937 rng2(chrono::steady_clock::now().time_since_epoch().count());
```

## Kiểm thử thời gian, không gian của code

Như mình đã đề cập ở trên, việc sinh test cũng có thể đuợc sử dụng để kiểm tra cũng như đảm bảo thời gian code chạy. Chẳng hạn như trong một kì thi offline, bạn code một thuật có độ phức tạp là $O(n\log^2{n})$ với $n = 200000$, tuy so sánh với test trâu đã đúng nhưng vẫn là khá sát với TL (thường là $1-2$s).

Để test code, ta chỉ cần chỉnh limit các biến trong test lên mức tối đa mà đề bài cho, cũng như bỏ code trâu (vì nếu để lại sẽ chạy rất lâu). Ngoài ra, để kiểm tra xem code chạy chính xác mất bao lâu trong một test, ta có thể sử dụng hàm $\texttt{clock}()$ như sau:

<details>
<summary>Spoiler</summary>
    
```cpp=
double time_before = (double)clock() / (double)CLOCKS_PER_SEC;
system((".\\" + NAME + ".exe").c_str());
double time_after = (double)clock() / (double)CLOCKS_PER_SEC;
cout << "TEST " << itest << " time: " << fixed << setprecision(10) << (time_after - time_before) << "\n";
```
</details>

Lưu ý: Hàm $\texttt{clock}()$ trả về số tick kể từ lúc code bắt đầu chạy đến thời điểm được gọi. Do đó, để biết được số giây đã trôi qua, ta chia $\texttt{clock}()$ cho $\texttt{CLOCKS_PER_SEC}$ -- số tick trên giây.

## Ví dụ về một trình chấm

Chúng ta sẽ lấy bài Comnet - bài $2$ VOI $2021$. Link đề bài tại [đây](https://oj.vnoi.info/problem/voi21_comnet)

Code chính (code ta muốn kiểm tra): 

<details>
  <summary>Code tham khảo</summary>
  
```cpp=
#include<bits/stdc++.h>
using namespace std;
 
#define int long long
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define foru(i, l, r) for(int i = l; i <= r; i++)
#define ford(i, r, l) for(int i = r; i >= l; i--)
 
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef pair<ii, ii> iiii;
 
const int N = 1e3 + 5;
 
const int oo = 1e18 + 7, mod = 1e9 + 7;
 
int n, k, a, b;
vector<int> Adj[N];
 
int dp[N][N][5], f[N][5];
 
int sz[N], ans;
 
void dfs(int u, int p){
    bool ck = 0;
    for(auto v : Adj[u]){
        if(v == p) continue;
        dfs(v, u);
        ck = 1;
    }
    dp[u][0][1] = dp[u][0][0] = 1;
    if(!ck){
        return;
    }
    sz[u] = 1;
    for(auto v : Adj[u]){
        if(v == p) continue;
        for(int i = 0; i <= sz[u]; i++){
            for(int j = 0; j <= k; j++){
                f[i][j] = dp[u][i][j];
                dp[u][i][j] = 0;
            }
        }
        for(int i = 0; i <= sz[u]; i++){
            for(int j = 0; j <= sz[v]; j++){
                for(int num1 = 0; num1 <= k; num1++){
                    for(int num2 = 0; num2 <= k; num2++){
                        if(num2 + num1 > k) continue;
                        dp[u][i + j + (num2 > 0)][num1 + num2] += f[i][num1] * dp[v][j][num2];
                    }
                }
            }
        }
        sz[u] += sz[v];
    }
    for(int i = a; i <= b; i++){
        ans += dp[u][i][k];
        for(auto v : Adj[u]){
            if(v == p) continue;
            ans -= dp[v][i - 1][k];
        }
    }
}
 
void process(){
    cin >> n >> k >> a >> b;
    for(int i = 1; i < n; i++){
        int x, y;
        cin >> x >> y;
        Adj[x].pb(y), Adj[y].pb(x);
    }
    dfs(1, 1);
    cout << ans << "\n";
}
 
signed main(){
    ios_base::sync_with_stdio(0);
    freopen("comnet.inp", "r", stdin);
    freopen("comnet.out", "w", stdout);
    process();
}
```
</details>

Code "trâu":

<details>
  <summary>Code tham khảo</summary>
  
```cpp=
#include<bits/stdc++.h>
using namespace std;
 
#define int long long
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define foru(i, l, r) for(int i = l; i <= r; i++)
#define ford(i, r, l) for(int i = r; i >= l; i--)
 
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef pair<ii, ii> iiii;
 
const int N = 2e3 + 5;
 
const int oo = 1e18 + 7, mod = 1e9 + 7;
 
int n, k, a, b;
 
int lca[N][N];
 
vector<int> nodes[N];
vector<int> Adj[N];
 
int root;
 
int d[N];
 
void dfs_small(int u, int p){
    for(auto v : Adj[u]){
        if(v == p) continue;
        d[v] = d[u] + 1;
        dfs_small(v, u);
    }
}
 
void dfs(int u, int p){
    if(u >= root) nodes[u].pb(u);
    for(auto v : Adj[u]){
        if(v == p) continue;
        d[v] = d[u] + 1;
        dfs(v, u);
    }
    for(auto v : Adj[u]){
        if(v == p) continue;
        for(auto w : nodes[v]) nodes[u].pb(w);
    }
    for(int itr1 = 0; itr1 < Adj[u].size(); itr1++){
        for(int itr2 = itr1 + 1; itr2 < Adj[u].size(); itr2++){
            int v1 = Adj[u][itr1], v2 = Adj[u][itr2];
            if(v1 == p || v2 == p) continue;
            for(int i = 0; i < nodes[v1].size(); i++){
                for(int j = 0; j < nodes[v2].size(); j++){
                    lca[nodes[v1][i]][nodes[v2][j]] = lca[nodes[v2][j]][nodes[v1][i]] = u;
                }
            }
        }
    }
    if(u >= root){
        for(auto v : nodes[u]){
            lca[u][v] = lca[v][u] = u;
        }
    }
}
 
void process(){
    cin >> n >> k >> a >> b;
    for(int i = 1; i < n; i++){
        int x, y;
        cin >> x >> y;
        Adj[x].pb(y);
        Adj[y].pb(x);
    }
    if(k == 2){
        int ans = 0;
        for(int i = 1; i <= n; i++){
            d[i] = 0;
            dfs_small(i, i);
            for(int j = i + 1; j <= n; j++){
                if(i == j) continue;
                if(d[j] >= a && d[j] <= b){
                    ans++;
                }
            }
        }
        cout << ans;
        return;
    }
    if(k == 3){
        int ans = 0;
        for(int i = 1; i <= n; i++){
            d[i] = 0;
            for(int j = 1; j <= n; j++) nodes[j].clear();
            root = i;
            dfs(i, i);
            for(int j = i + 1; j <= n; j++){
                for(int k = j + 1; k <= n; k++){
                    int temp = d[j] + d[k] - d[lca[j][k]];
                    //cout << i << " " << j << " " << k << " " << temp << "\n";
                    if(temp >= a && temp <= b){
                        ans++;
                    }
                }
            }
        }
        cout << ans;
        return;
    }
    if(k == 4){
        int ans = 0;
        for(int i = 1; i <= n; i++){
            d[i] = 0;
            for(int j = 1; j <= n; j++) nodes[j].clear();
            root = i;
            dfs(i, i);
            for(int j = i + 1; j <= n; j++){
                for(int k = j + 1; k <= n; k++){
                    for(int h = k + 1; h <= n; h++){
                        int temp = d[j] + d[k] - d[lca[j][k]];
                        temp += d[h] - max(d[lca[j][h]], d[lca[k][h]]);
                        if(temp >= a && temp <= b){
                            ans++;
                        }
                    }
                }
            }
        }
        cout << ans;
    }
}
 
signed main(){
    ios_base::sync_with_stdio(0);   
    freopen("comnet.inp", "r", stdin);
    freopen("comnet.ans", "w", stdout);
    process();
}
```
</details>    

Code sinh test (để debug):
<details>
<summary>Code tham khảo</summary>

```cpp=
#include<bits/stdc++.h>
using namespace std;
 
#define fi first
#define se second
#define pb push_back
 
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef pair<ii, ii> iiii;
 
const int N = 2e5 + 5;
 
// Tên bài
const string NAME = "comnet";
 
// Số test chúng ta muốn kiểm tra
const int TEST = 100;
 
// Đây là các số trong đề bài
int n, k, a, b;
 
// Trong code gen để debug, các bạn có thể giữ nguyên seed để đảm bảo lần nào generator cũng generate ra những test giống nhau.
// Như vậy, các bạn đảm bảo rằng code của mình thỏa mãn tất cả những test từng sai
mt19937 rng(7405);
 
// Còn nếu các bạn muổn random hoàn toàn có thể dùng
mt19937 rng2(chrono::steady_clock::now().time_since_epoch().count());
 
// Hàm này trả về một số bất kì trong khoảng [l, r]
int rnd(int l, int r){
    // rng() trả về một số bất kì
    return abs((int)rng() % (r - l + 1)) + l;
}
 
// Hàm này được dùng để tạo ra test
void generate_test(){
    // Chúng ta sinh test và xuất ra file .inp
    // Mỗi lần chúng ta xuất ra file .inp, ta sẽ in đè lên input cũ
    ofstream inp((NAME + ".inp").c_str());
    // Như các bạn có thể thấy, trong code debug chúng ta để n, k là những số nhỏ để dễ tìm hiểu test sai.
    // Ngoài ra n, k cũng cần đủ bé để code trâu chạy đủ nhanh
    n = rnd(3, 10);
    k = rnd(2, 4);
    a = rnd(2, n - 1);
    b = rnd(a, n - 1);
    inp << n << " " << k << " " << a << " " << b << "\n";
    for(int i = 2; i <= n; i++){
        // Ở đây mình sử dụng cách nối đỉnh i với một đỉnh bất kì trong khoảng [1, i - 1], đảm bảo tạo ra một cây thỏa mãn
        inp << rnd(1, i - 1) << " " << i << "\n";
    }
    // Ta cần đóng lại luồng này
    inp.close();
}
 
// Ở khá nhiều bài, việc check output chỉ đơn thuần là so sánh xem output của file .out và .ans có ra giống hệt nhau không.
// Đây là một trong những bài đó
bool check_test(){
    // Lệnh dưới đây kiểm tra hai file có giống hệt nhau hay không
    if(system(("fc " + NAME + ".out " + NAME + ".ans").c_str()) != 0){// 2 file khác nhau
        return 0;
    }
    else{
        return 1;
    }
}
 
// Hàm này được dùng để kiểm tra output của một bài bất kì
// Tuy không cần thiết cho bài này, nhưng sẽ hữu ích cho những bài khác
bool general_check_test(){
    // Ta nhập vào output từ file output được sinh ra từ 
    ifstream out1((NAME + ".out").c_str());
    ifstream out2((NAME + ".ans").c_str());
    int ans1 = -1, ans2 = -1;
    out1 >> ans1;
    out2 >> ans2;
    return (ans1 == ans2);
}
 
void process(){
    for(int itest = 1; itest <= TEST; itest++){
        generate_test();
        // 2 dòng tiếp theo để chạy 2 code mẫu và code trâu
        system((".\\" + NAME + ".exe").c_str());
        system((".\\" + NAME + "_trau.exe").c_str());
        bool ok = check_test();
        if(!ok){
            cout << "TEST " << itest << ": WA\n";
            exit(0);// Dừng lại ngay khi tìm được test sai
        }
        else{
            cout << "TEST " << itest << ": AC\n";
        }
    }
}
 
signed main(){
    // Việc không để ios_base::sync_with_stdio(0)/cin.tie(0) là để dễ xem trạng thái của từng test
    process();
}
```
</details>    

Code sinh test (để sinh lần cuối trước khi nộp bài) (optional):
<details>
<summary>Code tham khảo</summary>
    
```cpp=
#include<bits/stdc++.h>
using namespace std;
 
#define int long long
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define foru(i, l, r) for(int i = l; i <= r; i++)
#define ford(i, r, l) for(int i = r; i >= l; i--)
 
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef pair<ii, ii> iiii;
 
const int N = 2e3 + 5;
 
const int oo = 1e18 + 7, mod = 1e9 + 7;
 
int n, k, a, b;
 
int lca[N][N];
 
vector<int> nodes[N];
vector<int> Adj[N];
 
int root;
 
int d[N];
 
void dfs_small(int u, int p){
    for(auto v : Adj[u]){
        if(v == p) continue;
        d[v] = d[u] + 1;
        dfs_small(v, u);
    }
}
 
void dfs(int u, int p){
    if(u >= root) nodes[u].pb(u);
    for(auto v : Adj[u]){
        if(v == p) continue;
        d[v] = d[u] + 1;
        dfs(v, u);
    }
    for(auto v : Adj[u]){
        if(v == p) continue;
        for(auto w : nodes[v]) nodes[u].pb(w);
    }
    for(int itr1 = 0; itr1 < Adj[u].size(); itr1++){
        for(int itr2 = itr1 + 1; itr2 < Adj[u].size(); itr2++){
            int v1 = Adj[u][itr1], v2 = Adj[u][itr2];
            if(v1 == p || v2 == p) continue;
            for(int i = 0; i < nodes[v1].size(); i++){
                for(int j = 0; j < nodes[v2].size(); j++){
                    lca[nodes[v1][i]][nodes[v2][j]] = lca[nodes[v2][j]][nodes[v1][i]] = u;
                }
            }
        }
    }
    if(u >= root){
        for(auto v : nodes[u]){
            lca[u][v] = lca[v][u] = u;
        }
    }
}
 
void process(){
    cin >> n >> k >> a >> b;
    for(int i = 1; i < n; i++){
        int x, y;
        cin >> x >> y;
        Adj[x].pb(y);
        Adj[y].pb(x);
    }
    if(k == 2){
        int ans = 0;
        for(int i = 1; i <= n; i++){
            d[i] = 0;
            dfs_small(i, i);
            for(int j = i + 1; j <= n; j++){
                if(i == j) continue;
                if(d[j] >= a && d[j] <= b){
                    ans++;
                }
            }
        }
        cout << ans;
        return;
    }
    if(k == 3){
        int ans = 0;
        for(int i = 1; i <= n; i++){
            d[i] = 0;
            for(int j = 1; j <= n; j++) nodes[j].clear();
            root = i;
            dfs(i, i);
            for(int j = i + 1; j <= n; j++){
                for(int k = j + 1; k <= n; k++){
                    int temp = d[j] + d[k] - d[lca[j][k]];
                    //cout << i << " " << j << " " << k << " " << temp << "\n";
                    if(temp >= a && temp <= b){
                        ans++;
                    }
                }
            }
        }
        cout << ans;
        return;
    }
    if(k == 4){
        int ans = 0;
        for(int i = 1; i <= n; i++){
            d[i] = 0;
            for(int j = 1; j <= n; j++) nodes[j].clear();
            root = i;
            dfs(i, i);
            for(int j = i + 1; j <= n; j++){
                for(int k = j + 1; k <= n; k++){
                    for(int h = k + 1; h <= n; h++){
                        int temp = d[j] + d[k] - d[lca[j][k]];
                        temp += d[h] - max(d[lca[j][h]], d[lca[k][h]]);
                        if(temp >= a && temp <= b){
                            ans++;
                        }
                    }
                }
            }
        }
        cout << ans;
    }
}
 
signed main(){
    ios_base::sync_with_stdio(0);   
    freopen("comnet.inp", "r", stdin);
    freopen("comnet.ans", "w", stdout);
    process();
}
```
</details>    

## Template

Các bạn nhìn code generate ở trên thì có thể thấy khá dài, tuy nhiên template nếu đã nắm được thì có thể code chỉ trong $5-10$ phút, ngoài ra còn có thể áp dụng được cho tất cả các bài trong kì thi.

Code mẫu:
    
<details>
<summary>Code tham khảo</summary>
    
```cpp=
#include<bits/stdc++.h>
using namespace std;
 
// Tên bài
const string NAME = "";
 
// Số test chúng ta muốn kiểm tra
const int TEST = 100;
 
// Trong code gen để debug, các bạn có thể giữ nguyên seed để đảm bảo lần nào generator cũng generate ra những test giống nhau.
// Như vậy, các bạn đảm bảo rằng code của mình thỏa mãn tất cả những test từng sai
mt19937 rng(7405);
 
// Còn nếu các bạn muổn random hoàn toàn có thể dùng
mt19937 rng2(chrono::steady_clock::now().time_since_epoch().count());
 
// Hàm này trả về một số bất kì trong khoảng [l, r]
int rnd(int l, int r){
    // rng() trả về một số bất kì
    return abs((int)rng() % (r - l + 1)) + l;
}
 
// Hàm này được dùng để tạo ra test
void generate_test(){
    // Chúng ta sinh test và xuất ra file .inp
    // Mỗi lần chúng ta xuất ra file .inp, ta sẽ in đè lên input cũ
    ofstream inp((NAME + ".inp").c_str());
    // sinh test ở đây
    inp.close();
}
 
// Ở khá nhiều bài, việc check output chỉ đơn thuần là so sánh xem output của file .out và .ans có ra giống hệt nhau không.
// Đây là một trong những bài đó
bool check_test(){
    // Lệnh dưới đây kiểm tra hai file có giống hệt nhau hay không
    if(system(("fc " + NAME + ".out " + NAME + ".ans").c_str()) != 0){// 2 file khác nhau
        return 0;
    }
    else{
        return 1;
    }
}
 
// Hàm này được dùng để kiểm tra output của một bài bất kì
// Tuy không cần thiết cho bài này, nhưng sẽ hữu ích cho những bài khác
bool general_check_test(){
    // Ta nhập vào output từ file output được sinh ra từ 
    ifstream out1((NAME + ".out").c_str());
    ifstream out2((NAME + ".ans").c_str());
    // nhập vào dữ liệu của 2 file và check xem output của file .out có thỏa mãn không
 
}
 
void process(){
    for(int itest = 1; itest <= TEST; itest++){
        generate_test();
        // 2 dòng tiếp theo để chạy 2 code mẫu và code trâu
        system((".\\" + NAME + ".exe").c_str());
        system((".\\" + NAME + "_trau.exe").c_str());
        bool ok = check_test();
        if(!ok){
            cout << "TEST " << itest << ": WA\n";
            exit(0);// Dừng lại ngay khi tìm được test sai
        }
        else{
            cout << "TEST " << itest << ": AC\n";
        }
    }
}
 
signed main(){
    // Việc không để ios_base::sync_with_stdio(0)/cin.tie(0) là để dễ xem trạng thái của từng test
    process();
}
```
</details>

## Hướng dẫn sinh cho một số dạng bài

### Mảng

Việc sinh mảng khá đơn giản, chúng ta sinh random $N$ -- số phần tử của mảng -- và sau đó sinh tiếp ra $N$ số $A_1, A_2, ..., A_N$ là các phần tử của mảng. Ta có thể sinh $N$ cũng như các phần tử  nhỏ trước để khi tìm được test sai có thể debug được, còn việc sinh $N$ lớn có thể để kiểm tra lần cuối cùng.

Một số trường hợp các bạn có thể kiểm tra:
- Nhiều số trùng nhau, ít số phân biệt.
- N số khác nhau.
- Các số chạm limit.


### Đồ thị

Việc sinh đồ thị thì khó hơn việc sinh mảng một chút, cũng có nhiều phương pháp để sinh hơn.

Chẳng hạn như để sinh ra một cây (đồ thị với $N$ đỉnh và $N - 1$ cạnh), ta có một số cách sinh sau đây:

- Cách sinh đơn giản nhất:
    - Đầu tiên ta sinh ra $N$ -- số đỉnh của cây. 
    - Với mỗi đỉnh $i$ từ $2$ đến $N$, ta nối $i$ với một đỉnh bất kì trong khoảng $[1, i - 1]$. 
    - *(Tùy chọn)* Đảo lại thứ tự của các đỉnh.
  Đây là cách nhanh và an toàn nhất để sinh ra cây, tuy nhiên hai nhuợc điểm của cách sinh test này là cây sẽ có độ cao thấp (khoảng $\log{N}$) và bậc của các đỉnh (số cạnh nối với đỉnh đó) sẽ thấp (cũng chỉ là $O(\log{N}$)). 
  Ngoài ra, cây được sinh ra sẽ không hoàn toàn ngẫu nhiên. Những đỉnh có chỉ số thấp hơn thường sẽ có bậc cao hơn (đỉnh thứ $i$ sẽ có bậc kì vọng là $1 + \sum_{j = i + 1}^{n}\frac{1}{j - 1}$), và cây sẽ có xu hướng gần với đường thẳng hơn. 
- Sinh bằng Prüfer code: 
    - Đầu tiên ta sinh ra $N$ -- số đỉnh của cây. 
    - Sau đó, ta sinh $N - 2$ số $A_1, ..., A_{N - 2}$ trong khoảng $[1, N]$ - các số không nhất thiết phải phân biệt. Dựa vào dãy này, ta tạo ra cây bằng cách như sau:
    - Khi bắt đầu, chúng ta có $N$ đỉnh và chưa có cạnh nào
    - Ta định nghĩa $\texttt{deg}[i]$ với $1 \le i \le N$ là số lần xuất hiện của $i$ trong dãy $A_1, A_2, ..., A_{N - 2}$.
    - Ở bước thứ $i$ $(1 \le i \le N - 2)$, ta tìm vị trí $u$ nhỏ nhất có $\texttt{deg}[u] = 0$, nối đỉnh $u$ với đỉnh $A_i$, và trừ $\texttt{deg}[u]$ và $\texttt{deg}[A_i]$ đi $1$ (ta trừ $\texttt{deg}[u]$ để đảm bảo rằng không bao giờ chọn $u$ nữa).
    - Cuối cùng, ta nối $2$ đỉnh chưa được chọn với nhau.

  Việc sinh bằng Prüfer code cũng đơn giản, và vì mỗi dãy Prüfer tương ứng với một cây khác nhau, ta chắc chắn rằng cây được sinh ra là hoàn toàn ngẫu nhiên -- đây là ưu thế của việc sinh bằng Prüfer code so với cách sinh đầu tiên. Tuy nhiên để sinh ra những trường hợp đặc biệt thì các bạn vẫn cần sinh riêng, vì xác suất ra được những trường hợp này là rất thấp.
  
Ngoài ra khi sinh test các bạn có thể thử nghiệm với những loại cây đặc biệt như sau:
- Đỉnh $i$ nối với $(i + 1)$ với mọi $1 \le i < N$ (đường thẳng).
- Đỉnh $1$ nối với $(N - 1)$ đỉnh còn lại (ngôi sao).
- Đỉnh $\lfloor \frac{x}{2} \rfloor$ nối với đỉnh $x$ với $2 \le i \le N$ (cây nhị phân hoàn chỉnh).
- Ngoại trừ đỉnh $1$, các đỉnh còn lại có bậc $\le 2$ (đồ thị hình chữ $Y$).


### Chia căn

Một điểm các bạn có thể để ý của việc sinh test cho những bài chia căn là nếu sinh test bé như trên, thực tế chúng ta không kiểm tra đuợc việc chia căn có đúng hay không. Lý do cho việc này nằm ở việc những test bé có $N < S$ với $S$ là block size bạn đã chọn, và do đó tất cả các truy vấn sẽ bị dồn hết vào $1$ block. Khi đó code của chúng ta chạy không khác gì code trâu cả.

Để khắc phục vấn đề này, chúng ta có thể tạm thời sửa lại $S$ về một giá trị nhỏ hơn ($2, 3, 5$ chẳng hạn), và sau đó thử chạy code. Các bạn truớc khi nộp lưu ý sửa lại $S$ cũng như chạy lại code với $N$ lớn. 


### Hình học
Việc sinh test hình học không hề đơn giản, đặc biệt việc sinh ra những trường hợp biên (corner case). Với những kì thi offline (thường chấm điểm theo test), có thể những trường hợp biên này không làm mất quá nhiều điểm. Tuy nhiên, trong những kì thi mà việc đúng tất cả các test là cần thiết để có điểm (TST/APIO/IOI, ICPC, ...), thì việc nghĩ ra đuợc những trường hợp biên là vô cùng cần thiết. 

Những trường hợp biên hay gặp có thể kể đến:
- Các đường thẳng song song, trùng nhau.
- Các đường thẳng cắt nhau tại những điểm rất xa (chẳng hạn như hai đường thẳng đuợc tạo ra bởi $(0, 0), (0, 1)$ và $(0, 10^9), (10^9, 10^9 - 1)$). Việc tính toán giao điểm của những đường thẳng này có thể dẫn đến sai số lớn hơn sai số cho phép.
- Hai đường tròn giao nhau tại đúng 0/1/2 điểm.
- Các điểm nằm ở trục toạ độ, $3$ điểm thẳng hàng (có thể rơi vào trường hợp chia cho $0$).

Các bạn cũng lưu ý sinh test số bé, hoặc sinh những số tròn (chẳng hạn như $10^9, 10^9 - 1$) để dễ vẽ ra trong lúc debug.

## Luyện tập

>Trăm hay không bằng tay quen

Như rất nhiều việc khác trong cuộc sống, cách tốt nhất để sinh test tốt hơn, nhanh hơn cũng như có thói quen sinh test thay vì lười hay sợ tốn thời gian, đó chính là làm sinh test nhiều lần. 

Việc luyện tập sinh test thật ra khá đơn giản - bạn có thể sinh test với hầu hết tất cả các bài, miễn là có thể tạo ra code "trâu". Hãy đặt ra cho mình mục tiêu nộp chính xác luôn trong $1$ lần thông qua việc sinh test. Sau khi đã làm chủ việc sinh test, các bạn sẽ không cần phải sợ hãi trong những kì thi offline hay khi nhìn thấy dòng chữ "Wrong Answer" nữa.


