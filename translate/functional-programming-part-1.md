# Functional Programming - Phần 1

**Nguồn**: [Medium - So you want to be a functional programmer (part 1)](https://medium.com/@cscalfani/so-you-want-to-be-a-functional-programmer-part-1-1f15e387e536#.70yyalovu)

![translate_fp_revolution](https://cdn-images-1.medium.com/max/1600/1*AM83LP9sGGjIul3c5hIsWg.png)

Nếu bạn muốn trở thành một **functional programmer**, bước đầu tiên để hiểu thế nào là **Functional Programming** là bước quan trọng nhất, và đôi khi cũng là bước khó khăn nhất. Nhưng mọi chuyện sẽ dễ dàng hơn nếu bạn có một góc nhìn đúng đắn. Chuỗi bài viết này hi vọng có thể mang lại cho bạn điều đó.

### Forget everything you know - Học lại từ đầu

Học *functional programming* giống như bắt đầu từ con số không. Tất nhiên không hoàn toàn như vậy, sẽ có rất nhiều khái niệm tương tự như những gì bạn đã biết, nhưng bạn phải chuẩn bị sẵn tinh thần để *học lại* mọi thứ.

Với một quan điểm đúng đắn, bạn sẽ có một kì vọng đúng đắn và với một kì vọng đúng đắn, bạn sẽ không dễ dàng bỏ cuộc khi mọi thứ trở nên khó khăn.

Sẽ có rất nhiều thứ mà bạn đã và đang sử dụng khi lập trình sẽ không thể thực hiện được với *Functional Programming.*

Giống như khi bạn lái xe ô tô, bạn có thể sử dụng số lùi trong một vài trường hợp. Nhưng nếu bạn đang điều khiển máy bay hay tàu vũ trụ, sẽ không có số lùi nào cho bạn cả. Có thể bạn sẽ nghĩ: *Trời! Làm thế quái nào để lái nếu như không có số lùi chứ?*. Thì ra, máy bay hay tàu vũ trụ không cần số lùi vì chúng có thể di chuyển trong không gian ba chiều. Một khi bạn hiểu được điều này, bạn sẽ chẳng bao giờ nhớ đến số lùi nữa. Thực tế, một ngày nào đó bạn sẽ nghĩ rằng chiếc ô tô mà bạn vẫn quen lái hạn chế đến mức nào.

> Học Functional Programming sẽ mất thời gian. Vì vậy, hãy kiên nhẫn

Trong chuỗi bài viết này, tác giả sẽ trình bày những khái niệm, ý tưởng cơ bản nhất của *Functional Programming* để giúp các bạn có một nền tảng vững chắc trước khi bắt đầu thực sự với một **Functional Language** nào đó. Nếu bạn đã bước vào con đường này, những bài viết này sẽ giúp bạn củng cố thêm hiểu biết của mình.

Bạn không nên vội vàng. Hãy dành thời gian đọc thật kĩ từng khái niệm và đọc hiểu phần mã nguồn. Thậm chí bạn có thể dừng đọc sau mỗi phần để hiểu thật kĩ càng trước khi sang phần mới. Điều quan trọng nhất là bạn phải hiểu (**understand**).

### Purity (tính thuần khiết)

Khi một functional programmer nói về **Purity (tính thuần khiết)**, họ đang nói về những **Pure Function** (hàm thuần khiết).

Pure functions là những hàm rất đơn giản. Chúng có một đặc điểm: chỉ thực hiện thao tác trên những tham số được truyền vào:
```
var z = 10;
function add(x, y) {
    return x + y;
}
```
Hàm `add` KHÔNG tác động đến biến `z`. Nó không đọc giá trị từ `z` và cũng không cập nhật giá trị của `z`. Nó chỉ đọc giá trị của `x` và `y`, những đầu vào của nó và trả về kết quả phép cộng giữa hai giá trị đó.

Đó là một ví dụ về *pure function*, hay *hàm thuần khiết*. Nếu hàm `add` tác động vào `z`, nó sẽ không là *pure function* nữa.

Chúng ta cùng xem xét một hàm khác:
```
function justTen() {
    return 10;
}
```

Nếu hàm `justTen` là thuần khiết, nó chỉ có thể trả về một hằng số. Tại sao? Đơn giản vì nó không có tham số nào cả. Vì thế, để thoả mãn điều kiện của hàm thuần khiết, nó không thể tham chiếu đến bất kì một biến nào. Lựa chọn duy nhất của nó là trả về một hằng số.

Một hàm như vậy không nhận một tham số nào và không làm việc gì ngoài trả về một hằng số chắc chắn sẽ không có ích. Sẽ tốt hơn nếu định nghĩa `justTen` là một hằng số.

> Các hàm thuần khiết hữu ích phải nhận ít nhất một tham số.

Xem xét tiếp hàm sau đây:
```
function addNoReturn(x, y) {
    var z = x + y
}
```
Hãy để ý đến cách hàm này hoạt động: Nó nhận hai tham số `x` và `y`, thực hiện phép cộng giữa chúng và gán giá trị của kết quả vào biến `z` nhưng không trả về gì cả.

Đây cũng là một hàm thuần khiết vì nó chỉ tác động vào các tham số của nó. Nhưng vì hàm này không trả về gì cả, nên nó trở nên vô dụng.

> Một hàm thuần khiết hữu ích phải trả về một giá trị nào đó.

Hãy cùng xem xét lại hàm `add` ở trên:
```
function add(x, y) {
    return x + y;
}
console.log(add(1, 2)); // prints 3
console.log(add(1, 2)); // still prints 3
console.log(add(1, 2)); // WILL ALWAYS print 3
```
Ta có thể thấy rằng `add(1, 2)` luôn luôn bằng 3. Không quá ngạc nhiên, nhưng thực ra lí do duy nhất là vì `add` là một hàm thuần khiết. Nếu hàm `add` sử dụng giá trị từ bên ngoài, ta sẽ không bao giờ dự đoán được chắc chắn hành vi của nó.

> Hàm thuần khiết luôn luôn trả về cùng một đầu ra với cùng một đầu vào.

Vì hàm thuần khiết không thể thay đổi giá trị của biến bên ngoài, tất cả những hàm sau được coi là không thuần khiết (**impure**)
```
writeFile(fileName);
updateDatabaseTable(sqlCmd);
sendAjaxRequest(ajaxRequest);
openSocket(ipAddress);
```
Tất cả những hàm trên đều có cái được gọi là *tác dụng phụ* (**Side Effects**). Khi bạn gọi những hàm này, chúng thay đổi files, bảng trong cơ sở dữ liệu, gửi dữ liệu đến một máy chủ hay gọi đến hệ điều hành để lấy socket. Chúng không đơn thuần thao tác trên các tham số truyền vào và trả về một giá trị nào đó. Vì vậy, bạn không thể dự đoán chắc chắn rằng những hàm này sẽ trả về giá trị gì, kể cả với một đầu vào cho trước.

> Hàm thuần khiết KHÔNG có side effects (tác dụng phụ)

Trong các ngôn ngữ lập trình thông dụng như Javascript, Java hay C#, side effects có mặt khắp mọi nơi. Điều này khiến việc debug rất khó khăn vì giá trị của một biến có thể thay đổi ở bất cứ đâu trong chương trình của bạn. Khi bạn gặp một lỗi gây ra bởi việc một biến nào đó bị thay đổi sai giá trị hay sai thời điểm, bạn sẽ tìm kiếm ở đâu? Mọi nơi ư? Điều này chẳng tốt chút nào.

Tới đây, có thể bạn sẽ thắc mắc: "Làm thế quái nào để làm việc gì đó với chỉ những hàm thuần khiết?".

Trong Functional Programming, bạn không chỉ viết các hàm thuần khiết. Functional Programming không thể loại trừ hết các side effects mà chỉ có thể cô lập chúng. Vì chương trình phải tương tác với thế giới bên ngoài, nên một phần nào đó của chương trình phải là không thuần khiết (impure). Mục tiêu của Functional Programming là giảm thiểu tối đa lượng mã nguồn không thuần khiết và tách biệt chúng ra khỏi phần còn lại của chương trình.

### Immutability (tính bất biến)
![translate_fp_immutability](https://cdn-images-1.medium.com/max/1600/1*wKAhKZPXmcSwnq2AcLN-9Q.jpeg)

Bạn có nhớ khi lần đầu nhìn thấy những dòng code như thế này:
```
var x = 1;
x = x + 1;
```

Và có ai đó nói với bạn rằng bạn phải quên tất cả mọi thứ bạn học được trong môn Toán? Trong Toán học, `x` không bao giờ bằng `x+1`. 

Trong các ngôn ngữ lập trình thông dụng, điều đó là có thể và có nghĩa là bạn lấy giá trị hiện tại của `x`, công thêm `1` và gán kết quả trở lại biến `x`. 

Nhưng với functional programming, `x = x + 1` là sai quy tắc. Nên nếu bạn đã trót quên những gì bạn học được từ môn Toán, thì bây giờ bạn phải nhớ lại đấy.

> KHÔNG có biến (variables) trong Functional ProgrammingProgramming

Các giá trị được lưu vẫn được gọi là biến nhưng thực ra chúng là hằng số. Điều đó nghĩa là một khi `x` nhận một giá trị nào đó, `x` sẽ giữ giá trị đó cho đến hết vòng đời của nó trong chương trình. Phần lớn biến trong chương trình là biến địa phương (local variables), nên vòng đời của chúng tương đối ngắn. Nhưng một khi nó tồn tại, giá trị của nó không bao giờ thay đổi.

Sau đây là một ví dụ về một hằng biến (constant variable) trong Elm, một ngôn ngữ lập trình theo nguyên tắc Functional Programming được sử dụng phổ biến trong lĩnh vực phát triển Web:

```
addOneToSum y z =
    let
        x = 1
    in
        x + y + z
```

Trong ví dụ trên, `addOneToSum` là một hàm nhận 2 tham số `y` và `z`. Trong khối `let`, `x` được gán giá trị 1 và giữ nguyên giá trị nó cho đến hết vòng đời của nó. Vòng đời của nó kết thúc khi chương trình thoát khỏi hàm `addOneToSum` hay đúng hơn là sau khi khối `let` được thực hiện. Trong khối `in`, phép cộng được thực hiện bao gồm cả giá trị được định nghĩa trong khối `block` (`x`). Giá trị trả về là `x + y + z` hay chính xác hơn là `1 + y + z` vì `x = 1`.

Một lần nữa, chắc bạn sẽ phải thốt lên: "Làm thế quái nào để lập trình mà không dùng biến cơ chứ?"

Hãy nghĩ đến những trường hợp mà bạn muốn thay đổi giá trị của biến. Có hai trường hợp phổ biến mà bạn có thể nghĩ đến: thay đổi đa biến (ví dụ gán lại giá trị của một biến bất kì) hay thay đổi đơn biến (ví dụ như biến chạy trong vòng lặp).

Functional Programming giải quyết trường hợp đầu tiên bằng cách tạo ra một bản sao chép (copy) của những bản ghi (record) có giá trị thay đổi. Nó thực hiện điều đó một cách hiệu quả mà không phải sao chép toàn bộ bản ghi, bằng cách sử dụng những cấu trúc dữ liệu cho phép điều đó.

Trường hợp thứ hai cũng được giải quyết hoàn toàn tương tự, bằng cách tạo một bản sao chép của nó. Và bằng cách **không sử dụng vòng lặp**

Tất nhiên, điều đó không có nghĩa là chúng ta không thể sử dụng vòng lặp, chỉ đơn giản là Functional Programming không có những cấu trúc lặp như `for, while, do, repeat`,...

> Functional Programming sử dụng đệ quy để thực hiện vòng lặp.

Đoạn code sau minh hoạ hai cách để thực hiện vòng lặp trong Javascript:

```
// simple loop construct
var acc = 0;
for (var i = 1; i <= 10; ++i)
    acc += i;
console.log(acc); // prints 55
// without loop construct or variables (recursion)
function sumRange(start, end, acc) {
    if (start > end)
        return acc;
    return sumRange(start + 1, end, acc + start)
}
console.log(sumRange(1, 10, 0)); // prints 55
```

Hãy để ý cách tiếp cận thứ hai. Ở đây, hàm đệ quy cho kết quả giống như vòng lặp bằng cách gọi đến chính nó với một giá trị mới của `start` (`start + 1`) và một giá trị cộng dồn mới (`acc + start`). Nó không thay đổi giá trị của biến. Thay vào đó, nó sử dụng giá trị mới được tính từ những giá trị cũ của biến.

Tuy nhiên, bạn hiếm khi nhìn thấy đoạn code kiểu này trong Javascript. Một phần là bởi cú pháp của Javascript tương đối lộn xộn, phần khác là tư duy thông thường của bạn không nghĩ đến đệ quy.

Trong ngôn ngữ lập trình Elm, điều dó được thực hiện một cách dễ đọc và dễ hiểu hơn:

```
sumRange start end acc =
    if start > end then
        acc
    else
        sumRange (start + 1) end (acc + start) 
```

Hãy xem cách hoạt động của hàm `sumRange`:
```
sumRange 1 10 0 =      -- sumRange (1 + 1)  10 (0 + 1)
sumRange 2 10 1 =      -- sumRange (2 + 1)  10 (1 + 2)
sumRange 3 10 3 =      -- sumRange (3 + 1)  10 (3 + 3)
sumRange 4 10 6 =      -- sumRange (4 + 1)  10 (6 + 4)
sumRange 5 10 10 =     -- sumRange (5 + 1)  10 (10 + 5)
sumRange 6 10 15 =     -- sumRange (6 + 1)  10 (15 + 6)
sumRange 7 10 21 =     -- sumRange (7 + 1)  10 (21 + 7)
sumRange 8 10 28 =     -- sumRange (8 + 1)  10 (28 + 8)
sumRange 9 10 36 =     -- sumRange (9 + 1)  10 (36 + 9)
sumRange 10 10 45 =    -- sumRange (10 + 1) 10 (45 + 10)
sumRange 11 10 55 =    -- 11 > 10 => 55
55
```

Có thể bạn sẽ nghĩ rằng vòng lặp `for` dễ hiểu hơn so với cách làm này. Điều này tuỳ thuộc vào mức độ quen thuộc của bạn với những kiểu tư duy khác nhau. Nhưng những vòng lặp không sử dụng đệ quy yêu cầu sự khả biến (**mutability**) và điều này không tốt cho chương trình của bạn. Một lợi thế rõ ràng của kiểu đệ quy là trong chương trình của bạn, bạn chỉ có quyền đọc các giá trị của biến mà thôi (read access only). Điều này có nghĩa là không có bất kỳ người nào, kể cả bạn, có thể thay đổi giá trị của biến. Và như thế, sẽ không có lỗi nào phát sinh từ việc thay đổi giá trị của biến. 

Hơn nữa, nếu chương trình của bạn chạy đa luồng, không có luồng nào có thể thay đổi giá trị của một biến, dẫn tới việc luồng khác đọc sai giá trị của biến. Giá trị của một biến là không đổi và nếu một luồng muốn thay đổi giá trị đó, nó sẽ phải tạo một bản sao của biến.

> Sự bất biến (immutability) khiến code trở nên đơn giản và an toàn hơn.

**(Còn tiếp)**





