# Functional Programming - Phần 1

**Bài viết chưa hoàn thiện**

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

### Purity

Khi một functional programmer nói về **Purity (tính thuần khiết)**, họ đang nói về những **Pure Function*** (hàm thuần khiết).

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




