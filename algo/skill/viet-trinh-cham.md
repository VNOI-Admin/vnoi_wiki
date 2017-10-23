# Tự code, tự chấm, tự sướng - Bí kíp thi offline

**Tác giả**: Vũ *chipchip* Phúc Hoàng

Bạn cảm thấy lo sợ trong những kì thi chấm offline? Bạn bình thường làm bài rất tốt nhưng khi chấm offline lại bị điểm kém vì sai những lỗi vớ vẩn? Bạn code sai một bài rất khó và debug mãi không được vì không có test sai? Tất cả những vấn đề đó sẽ được giải quyết đơn giản với một chương trình chấm bài tự động, giúp bạn tự kiểm tra bài mình và phát hiện test sai. Bài viết này sẽ giới thiệu với bạn những bước cơ bản nhất để viết trình chấm - một kĩ thuật mà bạn nên thành thạo trước khi thi HSG Quốc gia.

[[_TOC_]]

# Trình chấm là gì?

Trình chấm là một bộ chương trình giúp bạn tự động sinh ra các test input ngẫu nhiên và tự động chạy hai chương trình lời giải khác nhau với các input đó để so sánh output. Về cơ bản, trình chấm gồm 4 chương trình là: lời giải 1, lời giải 2, trình sinh test, và trình so test. Thường thì lời giải 1 là cách chuẩn bạn sẽ sử dụng, còn lời giải 2 là một cách có hiệu quả kém hơn nhưng vẫn chính xác.

# Tại sao nên viết trình chấm?

Viết trình chấm là một trong những cách kiểm tra bài của mình đáng tin cậy nhất. Với những kì thi chấm offline, ví dụ như VOI, việc sai sót nhỏ rất khó tránh khỏi khi ta không thể biết kết quả trong khi thi. Vậy thì, nếu như bài của bạn không được chấm với bộ test của ban tổ chức, bạn hãy tự chấm nó với bộ test ngẫu nhiên mà mình sinh. Nếu bài của bạn đúng với các test ngẫu nhiên, bạn có thể tạm yên tâm là bài sẽ được điểm cao và không bị những sai sót "chí mạng" dẫn đến bài bị 0 điểm.

Trình chấm yêu cầu một trình "chuẩn" và một trình "trâu", và so sánh hai chương trình này với nhau. Nếu trình chấm của bạn phát hiện được một test mà kết quả hai chương trình không khớp nhau, trình chuẩn hoặc trình trâu của bạn sẽ sai, và bạn hãy sử dụng test đó để debug. Còn nếu tất cả các test đều đúng, bạn có thể tạm yên tâm, vì mặc dù có thể cả hai lời giải cùng sai, nhưng cùng sai giống hệt nhau thì rất khó.

Đối với những kì thi chấm online, hoặc đơn giản là bạn làm bài online trên mạng, trình chấm cũng rất hữu ích trong việc tìm test sai. Chẳng hạn khi bạn code một bài cấu trúc dữ liệu khó, nộp bài thấy bị 0 điểm, thay vì việc ngồi debug bằng mắt hãy thử code một bộ trình chấm để giúp tìm test sai. Với test sai tìm được bạn sẽ dễ dàng debug hơn rất nhiều.

Nhiều người ngại viết trình chấm vì cho rằng làm vậy mất thời gian. Tuy nhiên, khi đã thành thạo thì viết một bộ trình chấm cho một bài chỉ mất khoảng 10 phút, nếu như bài đó có thể làm trâu và sinh test ngẫu nhiên một cách dễ dàng. Lợi thế về mặt tâm lí khi đã biết chắc bài làm của mình đúng sẽ giúp bạn làm bài hiệu quả hơn, thực tế sẽ tiết kiệm được thời gian so với khi không kiểm tra bài. Tương tự, viết trình chấm để debug những bài code khó đôi khi hiệu quả hơn nhiều so với việc debug bằng mắt, tiết kiệm được rất nhiều thời gian.

# Khi nào nên viết trình chấm?

Lời khuyên của tác giả là: Hãy viết trình chấm bất cứ lúc nào mà bài có thể làm trâu và sinh test ngẫu nhiên dễ dàng. Có một số bài mà cách trâu còn khó hơn cách chuẩn thì có thể tạm bỏ qua, tuy nhiên nếu có thời gian vẫn nên viết trình chấm sau đấy để đảm bảo chắc chắn.

# Thành phần của một bộ trình chấm

**Lưu ý:** Bài viết này hướng dẫn cho Pascal/C++ trên hệ điều hành Windows. Với các ngôn ngữ khác hoặc chạy trên hệ điều hành khác, một số lệnh sẽ thay đổi, tuy nhiên ý tưởng vẫn tương tự.

Một bộ trình chấm gồm có 4 thành phần: Lời giải 1, lời giải 2, trình sinh test, trình so test.

## Lời giải 1:

Thường là code chuẩn của bạn. Dù viết trình chấm hay không thì phần này bắt buộc phải có nên cũng không cần phải nói nhiều. Trong bài viết này, ta sẽ giả sử input của trình lời giải 1 là `*.inp`, output là `*.out`.

## Lời giải 2:

Thường là code trâu, hoặc là một cách giải khác, miễn là ra đúng đáp số. Hãy chọn cách dễ code nhất, dễ đúng nhất có thể, vì thời gian chạy thực ra không quan trọng lắm khi bạn chỉ cần sinh test nhỏ để kiểm tra. Trong bài viết này, ta sẽ giả sử input của trình lời giải 2 là `*.inp`, output là `*.ans`.

## Trình sinh test:

Chương trình này có nhiệm vụ sinh input ngẫu nhiên vào file `*.inp`. Để cho hàm ngẫu nhiên được thay đổi khi chương trình khởi động, sử dụng lệnh `randomize` trong Pascal và `srand(time(NULL))` trong C++.

**Lưu ý:** Lệnh `srand(time(NULL))` trong C++ tính random theo giây, tức là sau 1 giây nó mới thay đổi random seed. Vì vậy nhiều khả năng các test random sinh ra liên tục sẽ bị giống nhau. Để khắc phục điều này, ta có thể lồng trình sinh test vào trình so test chứ không tách ra cho chạy riêng nữa. Với Pascal thì không phải lo về điều này, vì `randomize` thay đổi random seed theo mili giây.

## Trình so test:

Chương trình này có nhiệm vụ duyệt N lần, với N là số test cần so, mỗi lần thì chạy trình sinh test trước, xong đến lần lượt lời giải 1 và lời giải 2. Sau khi chạy xong, ta có được file `*.out` và `*.ans` tương ứng là kết quả của hai chương trình lời giải, và việc còn lại là so sánh 2 file này với nhau. Nếu kết quả trùng nhau (hoặc thỏa mãn điều kiện đề bài với những bài có nhiều đáp số), ta coi như test đó đúng và chuyển đến test sau. Nếu khác nhau, ta in ra sai và dừng chương trình lại luôn, và ta có 3 file `*.inp`, `*.out`, `*.ans` là dữ liệu của test sai.

Để chạy file, ta sử dụng `exec('*.exe', '')` trong Pascal và `system("*.exe")` trong C++.

# Ví dụ: Bài [VMELLIP](http://vn.spoj.com/problems/VMELLIP/)

Đây là một bài cấu trúc dữ liệu rất khó, thuộc đề thi VNOI Marathon 2015. Bài viết xin được lấy code của tanphatls987 được 90 điểm làm ví dụ.

## Lời giải 1:

[Link code](http://ideone.com/jd2XXQ/)

Đây là code của tanphatls987, được thêm 2 dòng `freopen` vào để mở file. Code gốc không có 2 dòng này vì nộp trên SPOJ sử dụng Standard Input / Output.

## Lời giải 2:

[Link code](http://ideone.com/4cIx5a/)

Đây là code trâu với độ phức tạp O(N * M), làm y như những gì đề bài bảo.

## Trình sinh test + Trình so test:

[Link code](http://ideone.com/PGDQEN/)

Vì đây là code C++ nên tác giả kết hợp trình sinh test với trình so test để cho hàm random chạy không bị trùng. Code sinh test từ dòng 11 đến dòng 37. Ở đây, ta duyệt 100 lần ứng với 100 test, mỗi lần duyệt ta sinh ngẫu nhiên ra file input `vmellip.inp`. Sau đó, ta lần lượt chạy hai chương trình ở trên: `system("vmellip.exe")` và `system("vmellip_trau.exe")` (lời giải 2 đặt tên là `vmellip_trau`). Sau đó ta sử dụng lệnh `system("fc vmellip.out vmellip.ans")`, có nhiệm vụ so hai file text `vmellip.out` và `vmellip.ans` với nhau. Nếu hai file hoàn toàn khớp nhau, lệnh `system` sẽ trả về exit code là 0, còn không sẽ trả về exit code là 1.

Chạy thử chương trình này, ta có thể sinh được một test sai như sau:

```
1 5
6 6 
3 1 1 8
1 1 1 1
6 1 1
1 1 1 9
2 1 1 8
9 8
```

Trong đó, lời giải 1 ra output là:

```
1
```

Lời giải 2 ra output là:

```
0
```

Giới hạn test (dòng 3) được đặt nhỏ, mục đích là để sinh ra test sai nhỏ dễ debug hơn. Sau khi code đã đúng, có thể tăng giới hạn lên để kiểm tra mạnh hơn.

# Làm sao để viết trình chấm một cách hiệu quả?

Qua ví dụ trên, bạn có thể cảm thấy khá ngại khi code trình so test khá dài, code có thể mất thời gian. Tuy nhiên, ta hoàn toàn có thể viết code so test thành một template để ứng dụng cho tất cả các bài! Với một template so test có sẵn, việc còn lại của ta chỉ là code phần sinh test và trình trâu, nếu như đã làm quen với trình chấm thì chỉ mất khoảng 10 phút để viết.

Tác giả xin được chia sẻ với các bạn các template trình chấm do chính mình sử dụng.

## Template dành cho C++:

```cpp
#include <bits/stdc++.h>
using namespace std;
// Tên chương trình
const string NAME = "template"; 
// Số test kiểm tra
const int NTEST = 100;

// Viết lại hàm random để sử dụng cho thuận tiện. Hàm random này sinh ngẫu nhiên số trong phạm vi long long, số sinh ra >= l và <= h.
long long Rand(long long l, long long h)
{
    return l + ((long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) * (RAND_MAX + 1) +
                (long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) +
                (long long)rand() * (RAND_MAX + 1) +
                rand()) % (h - l + 1);
}

int main()
{
    srand(time(NULL));
    for(int iTest = 1; iTest <= NTEST; iTest++)
    {
        ofstream inp((NAME + ".inp").c_str());
        // Code phần sinh test ở đây
        inp.close();
        // Nếu dùng Linux thì "./" + Tên chương trình
        system((NAME + ".exe").c_str());
        system((NAME + "_trau.exe").c_str());
        // Nếu dùng linux thì thay fc bằng diff
        if(system(("fc " + NAME + ".out " + NAME + ".ans").c_str()) != 0)
        {
            cout << "Test " << iTest << ": WRONG!\n";
            return 0;
        }
        cout << "Test " << iTest << ": CORRECT!\n";
    }
    return 0;
}
```

## Template dành cho Pascal:

```pascal
{$mode objfpc}
// Thư viện dos chứa lệnh exec
uses dos;
const
    // Tên chương trình
    NAM = 'template';
    // Số test kiểm tra
    NTEST = 100;
var
    iTest: integer;

begin
    for iTest := 1 to NTEST do
    begin
        // Pascal không gặp vấn đề với randomize, vì vậy ta có thể tách trình sinh test riêng ra.
        Exec(NAM + '_sinhtest.exe', '');
        Exec(NAM + '.exe', '');
        Exec(NAM + '_trau.exe', '');
	    Exec('fc', NAM + '.out ' + NAM + '.ans');
        if DosExitCode <> 0 then
        begin
            writeln('Test ', iTest, ': WRONG!');
            exit;
        end;
        writeln('Test ', iTest, ': CORRECT!');
    end;
end.
```

## Template dùng Shell script

Giả sử bạn có 2 code khác nhau, đã dịch ra 2 file executable là `prog1` và `prog2`. Bạn viết thêm 1 trình chấm và dịch ra file `gen`, `gen` nhận 1 argument là randomized seed (VD với C++ bạn dùng `srand(atoi(argv[1]))`):

```
# Sinh 100 test
for((i=1;i<=100;i++)); do
  # Sinh input với seed $i và lưu vào in_tmp
  ./gen $i > in_tmp
  # So sánh output của 2 code, nếu output khác nhau thì dừng lại.
  # Khi đó ta có file in_tmp chính là input mà 2 code chạy ra kết quả khác nhau.
  diff <(./prog1 < in_tmp) <(./prog2 < in_tmp) || break
done
```

# Luyện tập viết trình chấm

Để viết trình chấm thành thạo, hãy thử viết trình chấm với tất cả các bài mà bạn luyện tập, cho đến khi không còn ngại viết trình chấm nữa thì lúc đó bạn sẽ thành công. Hãy đặt ra mục tiêu là một sub AC với tất cả các bài mình làm với sự hỗ trợ của trình chấm. Một khi đã thành thạo tuyệt kĩ này, bạn sẽ dễ dàng chinh phục những kì thi chấm offline và không bao giờ phải lo lắng làm sai nữa.
