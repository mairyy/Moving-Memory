# Moving-Memory
Game Lật ảnh viết bằng ngôn ngữ C++ và sử dụng thư viện đồ họa SDL2
***
## Hướng dẫn cài đặt
**1. Tải code về máy**
  * Vào folder bất kì dự định lưu code (ví dụ: `D:\Code`)
  * Click chuột phải chọn `Open in Terminal`
  * Gõ lệnh `git clone https://github.com/mairyy/Moving-Memory.git`


**2. Chạy code**
  * Gõ lệnh `.\main.exe` để chạy chương trình

***
## Mô tả chung về trò chơi
  * **Moving Memory:** là game lật ảnh, màn hình sẽ hiện ra các bức hình đang úp, nhiệm vụ của người chơi là click mở các bức ảnh đó, nếu hai bức ảnh liên tiếp giống nhau thì chúng sẽ xuất hiện trên màn hình, ngược lại chúng sẽ úp trở lại.
  * **Các ý tưởng chính:**
    * Game với nhiều level khác nhau
    * Có âm thanh hình ảnh sinh động
    * Có menu
    * Tính điểm
    * Lưu điểm cao

***
## Mô tả các chức năng đã cài đặt
**_Video demo game: [Project game Moving Memory](https://youtu.be/TY6ALVZbTVs)_**
  * Menu khi bắt đầu vào game (_Start, Help, High Score_)
  * Có âm thanh khi click chuột, khi chọn đúng ảnh, chọn sai ảnh, khi chiến thắng màn chơi
  * Click chuột ảnh sẽ hiện lên, nếu 2 ảnh không giống nhau sẽ úp xuống
  * Game hiện tại có 3 level (_level 1 gồm 3 cặp ảnh, level 2 gồm 4 cặp ảnh và 1 ảnh dấu x, level 3 gồm 5 cặp ảnh và 2 ảnh dấu x_)
  * Tính điểm: chọn đúng ảnh được 100 điểm, chọn sai bị trừ 100 điểm (_với lần đầu lật bức ảnh đó sẽ không bị trừ điểm, riêng ảnh dấu x vẫn bị trừ_)
  * Lưu điểm cao

***
## Các kỹ thuật lập trình được sử dụng trong chương trình
  * **Mảng:** 
    * Sử dụng mảng tĩnh để lưu đường dẫn đến ảnh, lưu các vị trí của ảnh
    * Mảng động lưu các đối tượng Picture
  * **Con trỏ:**
    * Cấp phát mảng động
    * Các biến trong SDL (_`SDL_Surface, SDL_Texture,...`_)
    * Truyền địa chỉ cho hàm (_bên cạnh truyền tham biến_)
  * **Lớp:**
    * Lớp `Point` (_chỉ vị trí_)
    * Lớp `Picture` (_lưu thuộc tính của các ảnh dùng trong game, ví dụ: đường dẫn, vị trí,..._)
  * **Xử lí chuột:**
    * `SDL_Event`
    * Bắt xự kiện `SDL_PollEvent()`
  * **Đọc và ghi file:**
    * Đọc điểm cao trong file `highScore.txt` để in ra màn hình
    * Lưu điểm cao vào file `highScore.txt`
  * **Sinh số ngẫu nhiên** (_dùng để tạo vị trí ngẫu nhiên của các bức ảnh_)
  * **Đồ họa:**
    * Thư viện `SDL_image.h` để load và hiện ảnh ra màn hình (_sử dụng nhiều nhất trong chương trình_)
    * Thư viện `SDL_ttf.h` để load chữ lên màn hình (_hiện điểm và điểm cao_)
    * Thư viện `SDL_mixer.h` để load âm thanh (_tiếng click chuột, tiếng khi chọn đúng ảnh, khi chọn sai và khi hoàn thành level_)
  * **Chia nhỏ chương trình** thành các hàm, các file riêng để dễ quản lí

***
## Kết luận
**1. Kết luận:**
  Game đã có được các chức năng cơ bản có thể chơi được, tuy nhiên vẫn còn phải cải tiến nhiều để hoàn thiện hơn. 
  Về code của chương trình khá sạch đẹp dễ hiểu, tuy nhiên vẫn có nhiều chỗ chưa được tối ưu cần cải thiện trong tương lai.
  Một số tính năng đặt ra từ đầu vẫn chưa thực hiện được

**2. Hướng phát triển:**
Cải tiến code cho tối ưu hơn và thêm vào các tính năng chưa thực hiện được:
  * Đếm ngược thời gian chơi
  * Cho phép chọn level chơi (_hiện tại là chương trình tự động chuyển level sau khi hoàn thành level trước_)
  * Xử lí bàn phím để người chơi lưu tên khi đạt điểm cao
  * Có bảng xếp hạng (_lưu điểm và tên của 5 người được điểm cao nhất, hiện tại mới chỉ lưu 1 điểm cao nhât_)
  * Có thêm nút tạm dừng game, tạm dừng âm thanh
  * Thêm các lượt trợ giúp (_lật mở toàn bộ ảnh trong 3s, đóng băng thời gian 5s,..._)
  * Phần quà khi hoàn thành 1 level (_có thể là lượt trợ giúp, cộng điểm_)
  * Sau một thời gian các bức ảnh sẽ bị xáo trộn lại vị trí (_đây cũng là lí do em đặt tên game là Moving Memory nhưng hiện tại vẫn chưa thực hiện được_)
 
**3. Điều tâm đắc rút ra được sau khi hoàn thiện chương trình:**
Khi thực hiện dự án game này, em đã học thêm được nhiều kiến thức mới (_làm game có đồ họa bằng SDL2, tách file, viết Makefile, kĩ năng fix bugs, sử dung Github và viết file markdown này..._). 
Em cũng được trải nghiệm cảm giác rất mới lạ đó là tự tạo ra một game của chính mình, mang màu sắc cá tính riêng của mình. 
Và chỉ khi thực hiện game này, em mới thật sự thấy được một phần cách mà các lập trình viên tạo ra một chương trình, điều đó thực sự rất khó và cần kết hợp rất nhiều thứ (_từ tư duy, sáng tạo đến cả sự kiên nhẫn_)
Đặc biệt là sau khi làm dự án này em không thể chơi game một cách bình thường được :"((, mỗi khi chơi em luôn tự hỏi để code ra được game như này thì cần nhưng giai đoạn nào, khó như thế nào.
Tóm lại, khi thực hiện dự án này em đã học được nhiều điều mới, trải nghiệm cảm giác mới và có lẽ là thêm hứng thú với việc lập trình này hơn?
