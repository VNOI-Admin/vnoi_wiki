#Seam Carving Algorithm

[Nguồn](http://kirilllykov.github.io/blog/2013/06/06/seam-carving-algorithm/)

##Giới thiệu

Seam carving là một thuật toán dùng để thay đổi kích thước hình ảnh, nó được giới thiệu trong bài báo cáo khoa học của [S. Avidan & A. Shamir](http://www.win.tue.nl/~wstahw/edu/2IV05/seamcarving.pdf). Trong bài báo, nội dung chính của vấn việc thay đổi kích thước ảnh là việc loại bỏ đi các điểm ảnh ít nghĩa và giữ lại các điểm ảnh quan trọng. Bức ảnh dưới đây là sẽ họa điều này (ảnh gốc bên trên minh họa tấm ảnh 332x480 và ảnh bên dưới minh họa sau khi áp dụng thuật toán seam carving đẻ thu nhỏ còn lại kích thước là 272x400).

![](http://kirilllykov.github.io/images/seamcarving/sea-thai.jpg) 

![](http://kirilllykov.github.io/images/seamcarving/sea-thai-reduced.jpg)

Thuật toán này khá ấn tượng để có thể tìm thấy rất nhiều bài viết nói về nó. Tuy nhiên hầu hết đa số các tác giả đã không đọc bài báo cáo ban đầu và cung cấp cách cài đặt thuật toán khá cơ bản. Trong bài viết này tôi sẽ mô tả thuật toán cũng như tất cả các chi tiết như được viết bởi Avidan & Shamir. Tuy nhiên, ở bài viết này ta sẽ đi nghiên về cài đặt mà không đi sâu về chứng minh cụ thể. Ở đây ta sẽ sử dụng matlab để cài đặt thuật toán. Phần chứng minh cụ thể các bạn xem ở phần tham khảo.

##Năng lượng (Energy)

Để đơn giản hóa, ở bài viết chỉ tập trung nói việc làm giảm kích thước hình ảnh. Tuy nhiên việc làm tăng kích thước hình ảnh cũng làm tương tự, và sẽ được mô tả ở phần sau. Ý tưởng là việc loại bỏ các nội dung có ít ý nghĩa đối với người sử dụng (chứ ít thông tin). Ta gọi thông tin này là "Năng lượng" (Energy). Vì vậy ta sẽ giới thiệu hàm năng lượng để tính năng lượng điểm ảnh từ các điểm ảnh của ảnh gốc. Ví dụ, ở đây ta có thể tính năng lượng của ảnh thông qua đạo hàm của từng điểm ảnh theo các hướng: $e_{1}=\left | \frac{\delta I}{\delta x} \right | + \left | \frac{\delta I}{\delta y} \right |$. Nếu như ảnh có 3 kênh màu thì ta lấy tổng giá trị năng lượng của 3 kênh này lại với nhau. Đoạn code Matlab dưới đây sẽ mô tả quá trình tính. Hàm imfilter được áp dụng cho các điểm ảnh được đánh dấu, do đó kết quả dI(i, j)/dx = I(i+1)-I(i-1)/dx với dx = 1.

```matlab
function res = energyRGB(I)
% returns energy of all pixelels
% e = |dI/dx| + |dI/dy|
    res = energyGrey(I(:, :, 1)) + energyGrey(I(:, :, 2)) + energyGrey(I(:, :, 3));

function res = energyGrey(I)
% returns energy of all pixelels
% e = |dI/dx| + |dI/dy|
    res = abs(imfilter(I, [-1,0,1], 'replicate')) + abs(imfilter(I, [-1;0;1], 'replicate'));
end
```

Sơ đồ năng lượng ảnh sau khi tính:

![](http://kirilllykov.github.io/images/seamcarving/sea-thai-energy.jpg)

##Seam

Nếu chúng ta xóa đi các điểm ảnh có nặng lượng thấp theo một vị trí ngẫu nhiên, ta sẽ ra một hình ảnh méo mó. Nếu chúng ta xóa theo cột hoặc hàng với năng lượng tối hiểu, ta sẽ nhận được một bức ảnh hoàn chỉnh được thu nhỏ kích thước lại. Ở đây cột i nghĩa là {(i, j) với j được định nghĩa trước}, hàng - {(i, j) với i được định nghĩa trước}. Giải pháp được giới thiệu được khái quá hóa các dòng và cột (được gọi là đường seam). Nói đúng hơn, gọi I là một bức ảnh có kích thước $nxm$, một đường seam dọc là $(s^x)i = (i, x(j))s.t.\forall i, |x(i) - x(i - 1)| \leq 1$ trong đó $x[1..n] \to [1..m]$. Điều đó có nghĩa là, một đường seam dọc là một đường đi từ biên trên của bức ảnh xuống biên dưới của bức ảnh với độ dài đường đi bằng chiều rộng của bức ảnh, và với mỗi phần vị trí $(i, j)$ của đường seam, ta có thể đi tiếp đến các phần tử $(i + 1, j - 1)$, $(i + 1, j)$, $(i + 1, j + 1)$. Tương tự ta cũng có thể định nghĩa cho đường seam theo chiều ngang. Ví dụ về các đường màu đen là các đường seam trong hình dưới đây.

![](http://kirilllykov.github.io/images/seamcarving/sea-thai-seams.jpg)

Chúng ta sẽ tìm kiếm một đường seam sao cho có tổng giá trị năng lượng là nhỏ nhất (theo chiều chúng ta chọn): $s^*= [\min \limits_{s} \sum\limits_{i=1}^n e(I(s_{i}))]$. Cách để tìm được kết quả tối ưu cho bài toàn là sử dụng phương pháp quy hoạch động.

1. Tìm đường seam tối ưu từ biên trên của ảnh đến mỗi điểm ảnh $(i, j)$.
	+ Gọi $M[i, j]$ là giá trị năng lượng nhỏ nhất đi từ biên trên của ảnh đến điểm ảnh $(i, j)$.

	+ $M[1, j] = e(1, j)$ với $e(i, j)$ là năng lượng điểm ảnh tại $(i, j)$.

	+ $M[i, j] = min(M[i - 1, j - 1], M[i - 1, j], M[i - 1, j + 1]) + e(i, j)$.

2. Ở biên dưới của ảnh, ta tìm điểm đường seam tối ưu (tổng giá trị năng lượng thấp nhất thông qua bảng phương án $M$) và đi ngược về để tìm đường đi tối ưu.

Lưu ý: trong đoạn code dưới đây trả về một ma trận $nxm$ chỉ gồm 0 và 1 với các điểm ảnh trên đường đi seam sẽ có giá trị là 0 và ngược lại.

```matlab
function [optSeamMask, seamEnergy] = findOptSeam(energy)
% finds optimal seam
% returns mask with 0 mean a pixel is in the seam

    % find M for vertical seams
    % for vertical - use I`
    M = padarray(energy, [0 1], realmax('double')); % to avoid handling border elements

    sz = size(M);
    for i = 2 : sz(1)
        for j = 2 : (sz(2) - 1)
            neighbors = [M(i - 1, j - 1) M(i - 1, j) M(i - 1, j + 1)];
            M(i, j) = M(i, j) + min(neighbors);
        end
    end

    % find the min element in the last raw
    [val, indJ] = min(M(sz(1), :));
    seamEnergy = val;

    optSeamMask = zeros(size(energy), 'uint8');

    %go backward and save (i, j)
    for i = sz(1) : -1 : 2
        %optSeam(i) = indJ - 1;
        optSeamMask(i, indJ - 1) = 1; % -1 because of padding on 1 element from left
        neighbors = [M(i - 1, indJ - 1) M(i - 1, indJ) M(i - 1, indJ + 1)];
        [val, indIncr] = min(neighbors);

        seamEnergy = seamEnergy + val;

        indJ = indJ + (indIncr - 2); % (x - 2): [1,2]->[-1,1]]
    end

    optSeamMask(1, indJ - 1) = 1; % -1 because of padding on 1 element from left
    optSeamMask = ~optSeamMask;
end
```

Để tìm đường seam ngang, ta chỉ cần chuyển vị ma trận năng lượng lại.

##Tìm phương án tối ưu để xóa đường seam

Bây giờ ta có thể tính toán ra được đường seam và sử dụng đoạn code dưới đây, ta thậm chí có thể loại bỏ đường seam ra khỏi bức ảnh.

```matlab
function imageReduced = reduceImageByMaskVertical(image, seamMask)
    imageReduced = zeros(size(image, 1), size(image, 2) - 1, size(image, 3));
    for i = 1 : size(seamMask, 1)
        imageReduced(i, :, 1) = image(i, seamMask(i, :), 1);
        imageReduced(i, :, 2) = image(i, seamMask(i, :), 2);
        imageReduced(i, :, 3) = image(i, seamMask(i, :), 3);
    end
end

function imageReduced = reduceImageByMaskHorizontal(image, seamMask)
    imageReduced = zeros(size(image, 1) - 1, size(image, 2), size(image, 3));
    for j = 1 : size(seamMask, 2)
        imageReduced(:, j, 1) = image(seamMask(:, j), j, 1);
        imageReduced(:, j, 2) = image(seamMask(:, j), j, 2);
        imageReduced(:, j, 3) = image(seamMask(:, j), j, 3);
    end
end
```

Đây là một thuật toán hiệu quả để làm giám kích thước ảnh theo một chiều - chỉ cần việc tìm và xóa các đường seam nhiều lần như bạn cần. Nhưng nếu làm giảm kích thước theo cả hai chiều, ta cần phải làm như thế nào? Làm sao để quyết định rằng ở mỗi lần lắp đưa ra quyết định là xóa theo dòng hay cột sẽ tốt hơn? Vấn đề này một lần nữa được giải quyết bằng quy hoạch động. Ta gọi $T(i, j)$ là giá trị năng lượng thấp nhất khi ta loại bỏ i đường seam theo chiều dọc và j đường seam theo chiều ngang. Ta sử dụng thêm một mảng $transBitMask(i, j)$ lưu trữ đường đi đến $T(i, j)$ theo chiều dọc (1) hay ngang (0). Nhìn một đoạn code giả dưới đây để có thể dễ hình dung.

```
1) T(0, 0) = 0;
2) Intialize borders of T:
   for all j {
       T(0, j) = T(0, j - 1) + E(seamVertical);
   }
   for all i {
       T(i, 0) = T(j - 1, 0) + E(seamHorizontal);
    }
3) Initialize borders of TBM:
   for all j { T(0, j) = 1; }
   for all i { T(0, i) = 0; }
4) Fill in T and TBM (c-like pseudocode):
   for i = 2 to r {
       imageWithoutRow = image;
       for j = 2 to c {
            energy = computeEnergy(imageWithoutRow);

      horizontalSeamEnergy = findHorizontalSeamEnergy(energy);
      verticalSeamEnergy = findVerticalSeamEnergy(energy);
      tVertical = T(i - 1, j) + verticalSeamEnergy;
      tHorizontal = T(i, j - 1) _ horizontalSeamEnergy;
      if (tVertical < tHorizontal) {
         T(i, j) = tVertical;
         transBitMask(i, j) = 1
      } else {
         T(i, j) = tHorizontal;    
         transBitMask(i, j) = 0
      }
            // move from left to right - delete vertical seam
            imageWithoutRow = removeVerticalSeam(energy);
        }

        energy = computeEnergy(image);
        image = removeHorizontalSeam(energy);
    }
5) Go backward starting from T(r, c) and following the TBM.
```

Đoạn code thực thi bằng matlab

```matlab
function [T, transBitMask] = findTransportMatrix(sizeReduction, image)
% find optimal order of removing raws and columns

    T = zeros(sizeReduction(1) + 1, sizeReduction(2) + 1, 'double');
    transBitMask = ones(size(T)) * -1;

    % fill in borders
    imageNoRow = image;
    for i = 2 : size(T, 1)
        energy = energyRGB(imageNoRow);
        [optSeamMask, seamEnergyRow] = findOptSeam(energy');
        imageNoRow = reduceImageByMask(imageNoRow, optSeamMask, 0);
        transBitMask(i, 1) = 0;

        T(i, 1) = T(i - 1, 1) + seamEnergyRow;
    end;

    imageNoColumn = image;
    for j = 2 : size(T, 2)
        energy = energyRGB(imageNoColumn);
        [optSeamMask, seamEnergyColumn] = findOptSeam(energy);
        imageNoColumn = reduceImageByMask(imageNoColumn, optSeamMask, 1);
        transBitMask(1, j) = 1;

        T(1, j) = T(1, j - 1) + seamEnergyColumn;
    end;

    % on the borders, just remove one column and one row before proceeding
    energy = energyRGB(image);
    [optSeamMask, seamEnergyRow] = findOptSeam(energy');
    image = reduceImageByMask(image, optSeamMask, 0);

    energy = energyRGB(image);
    [optSeamMask, seamEnergyColumn] = findOptSeam(energy);
    image = reduceImageByMask(image, optSeamMask, 1);

    % fill in internal part
    for i = 2 : size(T, 1)

        imageWithoutRow = image; % copy for deleting columns

        for j = 2 : size(T, 2)
            energy = energyRGB(imageWithoutRow);

            [optSeamMaskRow, seamEnergyRow] = findOptSeam(energy');
            imageNoRow = reduceImageByMask(imageWithoutRow, optSeamMaskRow, 0);

            [optSeamMaskColumn, seamEnergyColumn] = findOptSeam(energy);
            imageNoColumn = reduceImageByMask(imageWithoutRow, optSeamMaskColumn, 1);

            neighbors = [(T(i - 1, j) + seamEnergyRow) (T(i, j - 1) + seamEnergyColumn)];
            [val, ind] = min(neighbors);

            T(i, j) = val;
            transBitMask(i, j) = ind - 1;

            % move from left to right
            imageWithoutRow = imageNoColumn;
        end;

        energy = energyRGB(image);
        [optSeamMaskRow, seamEnergyRow] = findOptSeam(energy');
         % move from top to bottom
        image = reduceImageByMask(image, optSeamMaskRow, 0);
    end;

end
```

##Phóng to hình hảnh

Để phóng to hình ảnh, thay vì ta loại bỏ đường seam ra khỏi ảnh, thì ta thêm một đường seam mới vào với giá trị trung bình của các điểm ảnh lận cận.

```matlab
function imageEnlarged = enlargeImageByMaskVertical(image, seamMask)

    avg = @(image, i, j, k) (image(i, j-1, k) + image(i, j+1, k))/2;

    imageEnlarged = zeros(size(image, 1), size(image, 2) + 1, size(image, 3));
    for i = 1 : size(seamMask, 1)
        j = find(seamMask(i, :) ~= 1);
        imageEnlarged(i, :, 1) = [image(i, 1:j, 1), avg(image, i, j, 1), image(i, j+1:end, 1)];
        imageEnlarged(i, :, 2) = [image(i, 1:j, 2), avg(image, i, j, 2), image(i, j+1:end, 2)];
        imageEnlarged(i, :, 3) = [image(i, 1:j, 3), avg(image, i, j, 3), image(i, j+1:end, 3)];
    end;
end

function imageEnlarged = enlargeImageByMaskHorizontal(image, seamMask)

    avg = @(image, i, j, k) (image(i-1, j, k) + image(i+1, j, k))/2;

    imageEnlarged = zeros(size(image, 1) + 1, size(image, 2), size(image, 3));
    for j = 1 : size(seamMask, 2)
        i = find(seamMask(:, j) ~= 1);
        imageEnlarged(:, j, 1) = [image(1:i, j, 1); avg(image, i, j, 1); image(i+1:end, j, 1)];
        imageEnlarged(:, j, 2) = [image(1:i, j, 2); avg(image, i, j, 2); image(i+1:end, j, 2)];
        imageEnlarged(:, j, 3) = [image(1:i, j, 3); avg(image, i, j, 3); image(i+1:end, j, 3)];
    end;
end
```


##Source code

```matlab
% (C) Copyright Kirill Lykov 2013.
%
% Distributed under the FreeBSD Software License (See accompanying file license.txt)

function image = seamCarving(newSize, image)
% apply seam carving to the image
% following paper by Avidan and Shamir '07
    sizeReductionX = size(image, 1) - newSize(1);
    sizeReductionY = size(image, 2) - newSize(2);
    
    mmax = @(left, right) max([left right]);
    
    image = seamCarvingReduce([mmax(0, sizeReductionX), mmax(0, sizeReductionY)], image);
    
    image = seamCarvingEnlarge([mmax(0, -sizeReductionX), mmax(0, -sizeReductionY)], image);
end

function image = seamCarvingReduce(sizeReduction, image)
    if (sizeReduction == 0)
        return;
    end;
    [T, transBitMask] = findTransportMatrix(sizeReduction, image);
    image = addOrDeleteSeams(transBitMask, sizeReduction, image, @reduceImageByMask);
end

% TODO Bug: enlarge gives artifacts althout I chouse different seams as described 
% in 4.3 in the paper
function image = seamCarvingEnlarge(sizeEnlarge, image)
    if (sizeEnlarge == 0)
        return;
    end;
    [T, transBitMask] = findTransportMatrix(sizeEnlarge, image);
    image = addOrDeleteSeams(transBitMask, sizeEnlarge, image, @enlargeImageByMask);
end

function [T, transBitMask] = findTransportMatrix(sizeReduction, image)
% find optimal order of removing raws and columns

    T = zeros(sizeReduction(1) + 1, sizeReduction(2) + 1, 'double');
    transBitMask = ones(size(T)) * -1;

    % fill in borders
    imageNoRow = image;
    for i = 2 : size(T, 1)
        energy = energyRGB(imageNoRow);
        [optSeamMask, seamEnergyRow] = findOptSeam(energy');
        imageNoRow = reduceImageByMask(imageNoRow, optSeamMask, 0);
        transBitMask(i, 1) = 0;

        T(i, 1) = T(i - 1, 1) + seamEnergyRow;
    end;

    imageNoColumn = image;
    for j = 2 : size(T, 2)
        energy = energyRGB(imageNoColumn);
        [optSeamMask, seamEnergyColumn] = findOptSeam(energy);
        imageNoColumn = reduceImageByMask(imageNoColumn, optSeamMask, 1);
        transBitMask(1, j) = 1;

        T(1, j) = T(1, j - 1) + seamEnergyColumn;
    end;

    % on the borders, just remove one column and one row before proceeding
    energy = energyRGB(image);
    [optSeamMask, seamEnergyRow] = findOptSeam(energy');
    image = reduceImageByMask(image, optSeamMask, 0);

    energy = energyRGB(image);
    [optSeamMask, seamEnergyColumn] = findOptSeam(energy);
    image = reduceImageByMask(image, optSeamMask, 1);

    % fill in internal part
    for i = 2 : size(T, 1)

        imageWithoutRow = image; % copy for deleting columns

        for j = 2 : size(T, 2)
            energy = energyRGB(imageWithoutRow);

            [optSeamMaskRow, seamEnergyRow] = findOptSeam(energy');
            imageNoRow = reduceImageByMask(imageWithoutRow, optSeamMaskRow, 0);

            [optSeamMaskColumn, seamEnergyColumn] = findOptSeam(energy);
            imageNoColumn = reduceImageByMask(imageWithoutRow, optSeamMaskColumn, 1);

            neighbors = [(T(i - 1, j) + seamEnergyRow) (T(i, j - 1) + seamEnergyColumn)];
            [val, ind] = min(neighbors);

            T(i, j) = val;
            transBitMask(i, j) = ind - 1;

            % move from left to right
            imageWithoutRow = imageNoColumn;
        end;

        energy = energyRGB(image);
        [optSeamMaskRow, seamEnergyRow] = findOptSeam(energy');
         % move from top to bottom
        image = reduceImageByMask(image, optSeamMaskRow, 0);
    end;

end

function image = addOrDeleteSeams(transBitMask, sizeReduction, image, operation)
% delete seams following optimal way
    i = size(transBitMask, 1);
    j = size(transBitMask, 2);

    for it = 1 : (sizeReduction(1) + sizeReduction(2))

        energy = energyRGB(image);
        if (transBitMask(i, j) == 0)
            [optSeamMask, seamEnergyRaw] = findOptSeam(energy');
            image = operation(image, optSeamMask, 0);
            i = i - 1;
        else
            [optSeamMask, seamEnergyColumn] = findOptSeam(energy);
            image = operation(image, optSeamMask, 1);
            j = j - 1;
        end;

    end;
end

function [optSeamMask, seamEnergy] = findOptSeam(energy)
% following paper by Avidan and Shamir `07
% finds optimal seam
% returns mask with 0 mean a pixel is in the seam

    % find M for vertical seams
    % for vertical - use I`
    M = padarray(energy, [0 1], realmax('double')); % to avoid handling border elements

    sz = size(M);
    for i = 2 : sz(1)
        for j = 2 : (sz(2) - 1)
            neighbors = [M(i - 1, j - 1) M(i - 1, j) M(i - 1, j + 1)];
            M(i, j) = M(i, j) + min(neighbors);
        end
    end

    % find the min element in the last raw
    [val, indJ] = min(M(sz(1), :));
    seamEnergy = val;
    
    %optSeam = zeros(sz(1), 1, 'int32');
    optSeamMask = zeros(size(energy), 'uint8');
    
    %indJ = indJ - 1; % because of padding on 1 element from left
 
    %go backward and save (i, j)
    for i = sz(1) : -1 : 2
        %optSeam(i) = indJ - 1;
        optSeamMask(i, indJ - 1) = 1; % -1 because of padding on 1 element from left
        neighbors = [M(i - 1, indJ - 1) M(i - 1, indJ) M(i - 1, indJ + 1)];
        [val, indIncr] = min(neighbors);
        
        seamEnergy = seamEnergy + val;
        
        indJ = indJ + (indIncr - 2); % (x - 2): [1,2]->[-1,1]]
    end
    %optSeam(1) = indJ; % to avoid if in loop becuase matlab is slow as hell

    optSeamMask(1, indJ - 1) = 1; % -1 because of padding on 1 element from left
    optSeamMask = ~optSeamMask;
    
end

function imageReduced = reduceImageByMask( image, seamMask, isVerical )
% removes pixels by input mask
% removes vertical line if isVerical == 1, otherwise horizontal
    if (isVerical)
        imageReduced = reduceImageByMaskVertical(image, seamMask);
    else
        imageReduced = reduceImageByMaskHorizontal(image, seamMask');
    end;
end

% could not find a more elegant way to do it
function imageReduced = reduceImageByMaskVertical(image, seamMask)
    imageReduced = zeros(size(image, 1), size(image, 2) - 1, size(image, 3));
    for i = 1 : size(seamMask, 1)
        imageReduced(i, :, 1) = image(i, seamMask(i, :), 1);
        imageReduced(i, :, 2) = image(i, seamMask(i, :), 2);
        imageReduced(i, :, 3) = image(i, seamMask(i, :), 3);
    end
end

function imageReduced = reduceImageByMaskHorizontal(image, seamMask)
    imageReduced = zeros(size(image, 1) - 1, size(image, 2), size(image, 3));
    for j = 1 : size(seamMask, 2)
        imageReduced(:, j, 1) = image(seamMask(:, j), j, 1);
        imageReduced(:, j, 2) = image(seamMask(:, j), j, 2);
        imageReduced(:, j, 3) = image(seamMask(:, j), j, 3);
    end
end

function imageEnlarged = enlargeImageByMask(image, seamMask, isVerical)
% removes pixels by input mask
% removes vertical line if isVerical == 1, otherwise horizontal
    if (isVerical)
        imageEnlarged = enlargeImageByMaskVertical(image, seamMask);
    else
        imageEnlarged = enlargeImageByMaskHorizontal(image, seamMask');
    end;
end

function imageEnlarged = enlargeImageByMaskVertical(image, seamMask)

    avg = @(image, i, j, k) (image(i, j-1, k) + image(i, j+1, k))/2;

    imageEnlarged = zeros(size(image, 1), size(image, 2) + 1, size(image, 3));
    for i = 1 : size(seamMask, 1)
        j = find(seamMask(i, :) ~= 1);
        imageEnlarged(i, :, 1) = [image(i, 1:j, 1), avg(image, i, j, 1), image(i, j+1:end, 1)];
        imageEnlarged(i, :, 2) = [image(i, 1:j, 2), avg(image, i, j, 2), image(i, j+1:end, 2)];
        imageEnlarged(i, :, 3) = [image(i, 1:j, 3), avg(image, i, j, 3), image(i, j+1:end, 3)];
    end;
end

function imageEnlarged = enlargeImageByMaskHorizontal(image, seamMask)

    avg = @(image, i, j, k) (image(i-1, j, k) + image(i+1, j, k))/2;

    imageEnlarged = zeros(size(image, 1) + 1, size(image, 2), size(image, 3));
    for j = 1 : size(seamMask, 2)
        i = find(seamMask(:, j) ~= 1);
        imageEnlarged(:, j, 1) = [image(1:i, j, 1); avg(image, i, j, 1); image(i+1:end, j, 1)];
        imageEnlarged(:, j, 2) = [image(1:i, j, 2); avg(image, i, j, 2); image(i+1:end, j, 2)];
        imageEnlarged(:, j, 3) = [image(1:i, j, 3); avg(image, i, j, 3); image(i+1:end, j, 3)];
    end;
end

function res = energyRGB(I)
% returns energy of all pixelels
% e = |dI/dx| + |dI/dy|
    res = energyGrey(I(:, :, 1)) + energyGrey(I(:, :, 2)) + energyGrey(I(:, :, 3));
end

function res = energyGrey(I)
% returns energy of all pixelels
% e = |dI/dx| + |dI/dy|
    res = abs(imfilter(I, [-1,0,1], 'replicate')) + abs(imfilter(I, [-1;0;1], 'replicate'));
end
```