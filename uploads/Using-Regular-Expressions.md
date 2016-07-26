[[_TOC_]]
# Sử dụng biểu thức chính quy (Using Regular Expressions) #

Nguồn: [Topcoder](https://www.topcoder.com/community/data-science/data-science-tutorials/using-regular-expressions-2/)

## Giới thiệu ##
Một **biểu thức chính quy** (*regular expression*) là một chuỗi ký tự đặc biệt dùng để mô tả một **mẫu tìm kiếm** (*search pattern*). Hẳn là nhiều bạn đã nhìn thấy hoặc dùng biểu thức chính quy trong các câu lệnh như ls(hoặc dir) \*.txt để liệt kê ra tất cả các file có đuôi txt. Biểu thức chính quy rất hữu dụng không chỉ trong việc tìm mẫu trùng khớp (*pattern matching*) mà còn  trong việc xử lý văn bản. Trong các kỳ SRMs thì biểu thức chính quy có thể cực kỳ hữu ích. Vài dòng code sử dụng biểu thức chính quy trong các bài toán xử lý text có thể khiến việc lập trình trở nên dễ thở hơn nhiều.

## Mô tả biểu thức chính quy ##
Một biểu thức chính quy (gọi tắt là regex) là một hoặc nhiều nhánh không rỗng, được phân cách bởi ký tự '|'. Biểu thức chính quy sẽ khớp với bất kỳ cái gì khớp với một trong các nhánh của nó. Biểu thức chính quy sau sẽ khớp với bất kỳ từ nào trong 3 từ "the", "top", "coder".
```
Biểu thức chính quy: the|top|coder
INPUT: Marius is one of the topcoders.
Tìm thấy "the" bắt đầu ở vị trí 17 và kết thúc ở vị trí 20.
Tìm thấy "top" bắt đầu ở vị trí 21 và kết thúc ở vị trí 24.
Tìm thấy "coder" bắt đầu ở vị trí 24 và kết thúc ở vị trí 29.
```
Một nhánh bao gồm một hoặc nhiều mảnh nối vào với nhau. Nó sẽ khớp với mảnh đầu tiên trước, rồi sau đó sẽ đến mảnh thứ 2, thứ 3, v.v.  
Một mảnh là  một nguyên tử (atom) có thể được theo sau bởi một trong các ký tự sau '\*', '+', '?', hoặc biên (*bound*). Một nguyên tử được theo sau bởi '\*' sẽ khớp với chuỗi nào có 0 hoặc nhiều hơn phần khớp với nguyên tử đó. Một nguyên tử được theo sau bởi '+' sẽ khớp với chuỗi nào có 1 hoặc nhiều hơn phần khớp với nguyên tử đó. Một nguyên tử được theo sau bởi '?' sẽ khớp với chuỗi nào có 0 hoặc 1 phần khớp với nguyên tử đó.  
Biểu thức chính quy sau sẽ khớp với chuỗi nào có chữ "top" và "coder" nối tiếp nhau:
```
Biểu thức chính quy: (top|coder)+
INPUT: This regex matches topcoder and also codertop.
Tìm thấy "topcoder" bắt đầu ở vị trí 19 và kết thúc ở vị trí 27.
Tìm thấy "codertop" bắt đầu ở vị trí 37 vả kết thúc ở vị trí 45.
```
Một biên được bắt đầu bởi '{' được theo sau bởi một số nguyên thập phân không dấu, có thể theo sau bởi dấu ',', có thể theo sau bởi một số nguyên thập phân không dấu và luôn kết thúc bởi '}'. Nếu có 2 số nguyên thì số thứ nhất sẽ không lớn hơn số thứ hai. Một nguyên tử theo sau bởi một biên chứa duy nhất một số nguyên i và không có dấu ',' nào thì sẽ khớp với xâu được ghép bởi đúng i nguyên tử. Một nguyên tử theo sau bởi một biên chứa duy nhất một số nguyên i có dấu ',' đằng sau thì sẽ khớp với xâu được ghép bởi i hoặc nhiều hơn i nguyên tử. Một nguyên tử theo sau bởi một biên chứa 2 số nguyên i, j sẽ khớp với xâu được ghép bởi i đến j nguyên tử.   
Biểu thức chính quy sau sẽ khớp với bất kỳ xâu nào có 2, 3 hoặc 4 ký tự '1':
```
Biểu thức chính quy: 1{2,4}
INPUT: 101 + 10 = 111 , 11111 = 10000 + 1111
Tìm thấy "111" bắt đầu ở vị trí 11 và kết thúc ở vị trí 14.
Tìm thấy "1111" bắt đầu ở vị trí 17 và kết thúc ở vị trí 21
Tìm thấy "1111" bắt đầu ở vị trí 33 và kết thúc ở vị trí 37.
```
Chúng ta có thể thấy rằng chuỗi dài nhất có thể sẽ được khớp và các đoạn được khớp sẽ không giao nhau. Một nguyên tử (atom) có thể là một biểu thức chính quy được đặt trong dấu ngoặc tròn '()' (khớp với cả biểu thức chính quy), một biểu thức ngoặc (xem ví dụ), '.' (khớp với bất kỳ ký tự nào), '^' (khớp với xâu rỗng ở đầu dòng), '\\$' (khớp với xâu rỗng ở cuối dòng), ký tự '\\\' được theo sau bởi một trong các ký tự '^.[$()|\*+?{\\\' (khớp với các ký tự đặc biệt tương ứng), hoặc đơn giản là một ký tự (khớp với ký tự đó). Có một loại nguyên tử khác là ký tự '\\\' được theo sau bởi một chữ số d khác 0. Nguyên tử này sẽ khớp với chuỗi ký tự giống với chuỗi ký tự được khớp bởi biểu thức con trong ngoặc tròn thứ d (đánh số ngoặc tròn bằng vị trí của mở ngoặc từ trái qua phải). Vì vậy mà '([bc])\1' sẽ khớp với 'bb' hoặc 'cc' và không khớp với 'bc'.   
Biểu thức chính quy sau đây khớp với một xâu được tạo bởi 2 chữ in thường giống nhau được phân cách bởi bất kỳ ký tự nào:
```
Biểu thức chính quy: ([a-z]+).\1
INPUT: top-topcoder|coder
Tìm thấy "top-top" bắt đầu ở vị trí 0 và kết thúc ở vị trí 7.
Tìm thấy "coder|coder" bắt đầu vở vị trí 7 và kết thúc ở vị trí 18.
```
Một biểu thức ngoặc là một danh sách các ký tự được viết trong dấu '[]'. Nó thường khớp với bất ký ký tự đơn nào ở trong danh sách. Nếu danh sách được bắt đầu bởi '^', nó sẽ khớp với bất kỳ ký tự nào không ở trong danh sách. Nếu 2 ký tự trong danh sách được phân cách bởi '-' thì có nghĩa là danh sách này bao gồm tất cả các ký tự nằm trong "đoạn" với 2 đầu là 2 ký tự đó (ví dụ '[0-9]' khớp với bất kỳ chữ số thập phân nào). Tất cả các ký tự (ngoại trừ ']', '^', '-'), kể cả ký tự đặc biệt đều mất đi tính chất đặc biệt của nó trong biểu thức ngoặc.  
Biểu thức chính quy sau đây khớp với các từ không bắt đầu bởi 'b', 'c', 'd' và kết thúc bởi 'at':
```
Biểu thức chính quy: [^b-d]at
INPUT: bat
Không tìm thấy xâu nào khớp.

Biểu thức chính quy: [^b-d]at
INPUT: hat
Tìm thấy "hat" bắt đầu ở vị trí 0 và kết thúc ở vị trí 3.
```
Ví dụ sau đây sẽ bao gồm hầu hết các định nghĩa ở phía trên đã nêu. Nó sẽ khớp với một cặp HTML tag đóng/mở và nội dung giữa 2 tag này.
```
Biểu thức chính quy: <([a-zA-Z][a-zA-Z0-9]*)(()| [^>]*)>(.*)</\1>
INPUT: <font size="2">Topcoder is the</font> <b>best</b>
Tìm thấy "<font size="2">Topcoder is the</font>" bắt đầu ở vị trí 0 và kết thúc ở vị trí 37.
Tìm thấy "<b>best</b>" bắt đầu ở vị trí 38 và kết thúc ở vị trí 49.
```
([a-zA-Z][a-zA-Z0-9]\*) sẽ khớp với bất kỳ từ nào bắt đầu bởi một chữ cái và tiếp tục bởi một số lượng chữ cái hoặc chữ số bất kỳ.  
(()| [^>]\*) sẽ khớp với xâu rỗng hoặc bất kỳ xâu nào không chứa '>'.  
\1 sẽ khớp với xâu nào mà ([a-zA-Z][a-zA-Z0-9]\*) đã khớp trước đó.  
Mô tả trên là mô tả sơ qua về biểu thức chính quy cơ bản. Một biểu thức chính quy được viết bởi các luật trên sẽ chạy được ở Java(>=1.4) và C++(POSIX EXTENDED). Để tìm hiểu sâu hơn về các mở rộng được cung cấp bởi các ngôn ngữ khác mời các bạn xem phần tham khảo.

## Sử dụng biểu thức chính quy ##

### Trong Java ###
Trong Java (từ 1.4 trở lên) có một gói (*package*) tên là "java.util.regex" cho phép sử dụng biểu thức chính quy.  
Gói này bao gồm 3 lớp (*class*): Pattern, Matcher, PatternSyntaxException.
- Một đối tượng (*object*) Pattern là một biểu thức chính quy đã được biên dịch. Lớp Pattern không cung cấp public constructors. Để tạo ra một mẫu, bạn phải sử dụng một trong các phương thức biên dịch của nó và chúng sẽ trả về một đối tượng Pattern. 
- Đối tượng Matcher sẽ tiến hành thông dịch mẫu và khớp với input. Giống như lớp Pattern, Matcher không có public constructors. Để tạo ra một đối tượng Matcher bạn phải sử dụng phương thức của lớp Matcher trên một đối tượng Pattern và nó sẽ trả về một đối tượng Matcher. 
- Đối tượng PatternSyntaxException là unchecked exception chỉ ra lỗi cú pháp của biểu thức chính quy.

Ví dụ (lấy từ [4]):
```java
Pattern pattern;
Matcher matcher;
pattern = Pattern.compile(<REGEX>);
matcher = pattern.matcher(<INPUT>);
boolean found;
while(matcher.find()) {
  System.out.println("Found the text \"" + matcher.group() +  "\" starting at index " + matcher.start() +
      " and ending at index " + matcher.end() + ".");
  found = true;
}

if(!found){
  System.out.println("No match found.");
}
```
Java cũng cung cấp các phương thức sau trong lớp String:
- boolean matches(String regex): kiểm tra xem xâu hiện tại có khớp với regex không.
- String replaceAll(String regex, String replacement): Thay tất cả các xâu con của xâu hiện tại mà khớp với regex bằng xâu replacement.
- String replaceFirst(String regex, String replacement): Thay xâu con đầu tiên của xâu hiện tại mà khớp với regex bằng xâu replacement.
- String[] split(String regex): Chia xâu hiện tại thành nhiều xâu sử dụng các xâu con khớp với regex làm phân cách. 


### Trong C++ ###
Nhiều topcoders cho rằng biểu thức chính quy là một trong những điểm mạnh của Java so với C++. Tuy nhiên các coders sử dụng C++ cũng không hề nản chí vì biểu thức chính quy cũng có thể được sử dụng trong C++. 

Có nhiều thư viện hỗ trợ biểu thức chính quy cho C++, tuy nhiên chúng không tương thích với nhau tốt cho lắm.  Một điều may mắn đó là bạn có thể chọn lựa một trong các thư viện này để sử dụng và không phải lo là nó không tương thích với nhau. Nếu bạn muốn dùng biểu thức chính quy ở arena bạn phải lựa chọn giữa 2 APIs: POSIX_regex và GNU_regex. Để sử dụng 2 APIs này bạn phải thêm header "regex.h". Cả 2 APIs đều được thực hiện qua 2 bước. Đầu tiên sẽ có một hàm biên dịch biểu thức chính quy, sau đó sẽ có một hàm khớp/tìm biểu thức chính quy đã được biên dịch với xâu cần khớp. 
Sau đây sẽ là mô tả ngắn gọn về 2 APIs này để cho các bạn có thể chọn lựa bạn thích cái nào hơn.

#### POSIX_regex ####
POSIX_regex hỗ trợ 2 kiểu biểu thức chính quy khác nhau: cơ bản và mở rộng. Biểu thức chính quy cơ bản tương tự như trong ed, trong khi biểu thức chính quy mở rộng tương tự như trong egrep, thêm vào các phép toán '|', '+', '?' và không yêu cầu '\' ở các biểu thức con viết trong ngoặc đơn '()' hoặc các biên được viết trong ngoặc nhọn '{}'. Kiểu cơ bản là mặc định, nhưng kiểu mở rộng được ưa thích hơn.  
Với POSIX, bạn chỉ có thể tìm kiếm biểu thức chính quy mà không thể khớp được. Để khớp được, bạn phải biên dịch nó thành một pattern buffer, sử dụng 'regcomp'. Một khi đã biên dịch thành pattern buffer bạn có thể tìm kiếm trong một xâu kết thúc bằng null bằng cách dùng 'regexec'. Nếu một trong hai hàm 'regcomp' và 'regexec' gặp lỗi nó sẽ trả về error code. Để biết được lỗi là gì bạn dùng 'regerror'. Để giải phóng bộ nhớ của pattern buffer bạn dùng 'regfree'.   
Để biết cách sử dụng chi tiết mời các bạn xem mục [2] và [3] ở phần tham khảo. 

#### Ví dụ: ####
Sau đây là một ví dụ về cách sử dụng các hàm này:
```cpp
regex_t reg;

string pattern = "[^tpr]{2,}";
string str = "topcoder";

regmatch_t matches[1];

regcomp(&reg,pattern.c_str(),REG_EXTENDED|REG_ICASE);

if (regexec(&reg,str.c_str(),1,matches,0)==0) {
  cout << "Match "
  cout << str.substr(matches[0].rm_so,matches[0].rm_eo-matches[0].rm_so)
  cout << " found starting at: "
  cout << matches[0].rm_so
  cout << " and ending at "
  cout << matches[0].rm_eo
  cout << endl;
} else {
  cout << "Match not found."
  cout << endl;
}
regfree(&reg);
```


#### GNU_regex ####
GNU_regex API có nhiều hàm hơn. Với các hàm của GNU_regex các bạn có thể khớp một xâu với mẫu và cũng có thể tìm kiếm mẫu ở trong xâu. Việc sử dụng các hàm này cũng tương tự như việc sử dụng các hàm của POSIX: đầu tiên một mẫu cần phải được biên dịch sử dụng 're_compile_pattern', sau đó nhận được pattern buffer và nó được dùng để tìm và khớp. Các hàm sử dụng cho tìm kiếm và khớp là 're_search' và 're_match'. Trong trường hợp tìm kiếm thì fastmap có thể được sử dụng để tối ưu việc tìm kiếm. Nếu không có fastmap thuật toán tìm kiếm sẽ khớp các mẫu ở các vị trí liên tiếp nhau trong xâu. Fastmap sẽ chỉ ra vị trí của ký tự bắt đầu tìm kiếm. Fastmap được tạo bằng cách gọi 're_compile_fastmap'. GNU_regex còn có hàm 're_search2' và 're_match2' cho việc tìm kiếm và khớp với những data tách rời.  Để giải phóng bộ nhớ của pattern buffer bạn dùng 'regfree'.   
Để biết cách sử dụng chi tiết mời các bạn xem mục [3] ở phần tham khảo. 


#### Ví dụ: ####
```cpp
string pattern = "([a-z]+).\\1";
string str = "top-topcoder|coder";

re_pattern_buffer buffer;
  char map[256];

buffer.translate = 0;
buffer.fastmap = map;
buffer.buffer = 0;
buffer.allocated = 0;

re_set_syntax(RE_SYNTAX_POSIX_EXTENDED);
const char* status = re_compile_pattern(pattern.c_str(),pattern.size(),&buffer);
if (status) {
    cout << "Error: " << status << endl;
}
re_compile_fastmap(&buffer);

struct re_registers regs;
int ofs = 0;
if (re_search(&buffer,str.c_str(),str.size(),0,str.size(),&regs)!=-1) {
  cout << "Match "
  cout << str.substr(regs.start[0],regs.end[0]-regs.start[0])
  cout << " found starting at: "
  cout << regs.start[0]
  cout << " and ending at "
  cout << regs.end[0]
  cout << endl;
} else {
  cout << "Match not found."
  cout << endl;
}
regfree(&buffer);
```

### Ví dụ trong các cuộc thi SRMs: ###
Các ví dụ phía dưới được viết bằng Java. Bạn nào dùng C++ có thể dùng POSIX hoặc GNU regex APIs  để viết các hàm tương đương trong Java (replace_all, split, matches).  
**[CyberLine](http://community.topcoder.com/stat?c=problem_statement&pm=2396&rd=4755) (SRM 187 div 1, level 1)**  
```java
import java.util.*;
public class Cyberline
{
  public String lastCyberword(String cyberline)
  {
    String[]w=cyberline.replaceAll("-","")
          .replaceAll("[^a-zA-Z0-9]"," ")
          .split(" ") ;
    return w[w.length-1];
  }
}
```
**[UnLinker](http://community.topcoder.com/stat?c=problem_statement&pm=2912&rd=5849) (SRM 203 div 2, level 3)**  
```java
import java.util.*;
public class UnLinker
{
  public String clean(String text)
  {
    String []m = text.split("((http://)?www[.]|http://)[a-zA-Z0-9.]+[.](com|org|edu|info|tv)",-1);
    String s = m[0] ;
    for (int i = 1 ; i < m.length ; ++i)
      s = s + "OMIT" + i + m[i] ;
    return s ;
  }
}
```
**[CheatCode](http://community.topcoder.com/stat?c=problem_statement&pm=1779&rd=4575) (SRM 154 div 1, level 1)**
```java
import java.util.*;
public class CheatCode {
  public int[] matches(String keyPresses, String[] codes) {
    boolean []map = new boolean[codes.length] ;
    int count = 0 ;
    for (int i=0;i<codes.length; ++i)
    {
      String regex = ".*" ;
      for (int j=0; j<codes[i].length(); ) {
        int k = 1;
        while ((j+k)<codes[i].length() && codes[i].charAt(j+k)==codes[i].charAt(j)) k++;
        regex = regex + codes[i].charAt(j) + "{"+k+",}";
        j+=k;
      }

      regex = regex + ".*" ;
      if (keyPresses.matches(regex))
      {
        map[i] = true ;
        count++ ;
      }
    }
    int []res = new int[count] ;
    int j=0;
    for (int i= 0 ; i < codes.length; ++i)
      if(map[i] == true)
        res[j++]=i ;
    return res ;
  }
}
```


## Tham khảo ##
1. Xem trang hướng dẫn của linux: regex(7) 
2. Xem trang hướng dẫn của linux: regex(3)
3. [[http://docs.freebsd.org/info/regex/regex.info.Programming_with_Regex.html|http://docs.freebsd.org/info/regex/regex.info.Programming_with_Regex.html]]
4. [[http://www.regular-expressions.info/|http://www.regular-expressions.info/]]
5. [[http://java.sun.com/docs/books/tutorial/extra/regex/|http://java.sun.com/docs/books/tutorial/extra/regex/]]

