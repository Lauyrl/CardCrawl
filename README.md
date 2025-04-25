- Cách chạy: cho tệp 'assets' vào tệp 'bin' rồi chạy cc.exe

### Cấu trúc:

<br/>
1, Những bộ phận chính của code bao gồm các file định nghĩa và quản lý thẻ bài, vật phẩm, các đối tượng (nhân vật và quái) và các trạng thái của game
<br/>
- Hầu hết những yếu tố của game sử dụng key + map để khởi tạo để dễ quản lý, tránh phải viết một hàm if else riêng để định nghĩa các object
<br/>
2, Tương tác, diễn biến game:
<br/>
- Các game state được quản lý bởi biến Game::gameState, dựa vào biến này, hàm Game::update() sẽ gọi hàm display phù hợp
<br/>
- Mọi tác động vào nhân vật và bộ thẻ sẽ sử dụng các biến global Character::ironclad và Deck::deck được khởi tạo trước vòng lập main
<br/>
- Riêng đối với tương tác giữa thẻ và quái trong combat, hàm Card::activate sẽ nhận vào vector stageEnemies và index của mục tiêu chính để thực hiện hiệu ứng
<br/>
<br/>


### Tính năng chính:
+ Mọi thao tác đều bằng chuột
<br/>

#### Map:
+ Một khi bắt đầu game, một map sẽ được tạo ra với những node(điểm) được nối vào nhau
<br/>
+ Map có dạng tương đương với mảng 2D, và luôn có 20 'hàng' và 5 'cột', mỗi ô chứa nhiều nhất một node
<br/>

#### Có 5 loại node:
<br/>
- Combat

+ Combat diễn ra theo lượt, lượt chắn là lượt của người chơi, lượt lẻ là lượt của quái

+ Khi bắt đầu lượt chơi, người chơi chọn giữa ít nhất 5 thẻ được bốc để tác động vào quái hoặc nhân vật, để phòng vệ hoặc tấn công, cho đến khi hết năng lượng;
Đồng thời, tất cả quái sẽ random ra một hành động để thực hiện sau khi lượt của người chơi kết thúc: hành động được chọn sẽ thể hiện bằng một đồ hoạ trên đầu quái (cùng với một đoạn miêu tả ngắn khi di chuột lên), người chơi có thể sử dụng thông tin này để phản ứng (vd: tạo khiên nếu quái chuẩn bị tấn công)  

+ Cả nhân vật và quái đều có thể tạo ra các buff, debuff cơ bản (vd: nhận ít/nhiều dmg hơn)

+ Sau khi thắng combat, người chơi nhận 3 phần thưởng: vàng, 1 vật phẩm và 1 thẻ bài

+ Hệ thống quản lý thẻ: trong combat, thẻ của người chơi được quản lý bằng 3 'hộp' - hộp bốc thẻ(draw pile), 'tay' người chơi, hộp bỏ thẻ(discard pile). Bắt đầu lượt chơi, 5 thẻ ngẫu nhiên được đẩy từ draw pile vào tay người chơi, sau khi sử dụng một thẻ, nó sẽ bị đẩy vào discard pile, một khi kết thúc lượt, những thẻ còn lại chưa được sử dụng sẽ bị đẩy vào discard pile; Một khi draw pile hết thẻ, tất cả thẻ từ discard pile sẽ được đẩy vào draw pile (trường hợp đặc biệt: những thẻ thuộc loại Power, hay những thẻ có từ khoá 'Exhaust' chỉ được sử dụng 1 lần và sẽ biến mất khỏi combat hiện tại)

<br/>
- Treasure: cho người chơi vàng và 1 vật phẩm (sử dụng chung yếu tố phần thưởng của combat)

<br/>
- Rest: hồi một % máu cho nhân vật

<br/>
- Shop: Sử dụng vàng để mua thẻ và vật phẩm, hoặc sử dụng 75 vàng để xoá một thẻ khỏi bộ thẻ

<br/>
- Event: những sự kiện có tính tương tác (một số ví dụ: cho phép người chơi chọn một thẻ để xoá/copy, đổi một thẻ để hồi máu, đổi vàng để hồi máu,...(hiện tại game chưa có nhiều sự kiện khác nhau))

<br/>
- Những phần thưởng từ shop, combat hay treasure có độ hiếm khác nhau, mỗi loại thẻ có thể sở hữu vô số, riêng vật phẩm mỗi loại chỉ có 1 (sau khi nhận được sẽ bị erase khỏi std::set)

<br/>
<br/>
* Đồ hoạ:
<br/>
- Đồ hoạ thô sơ với các sprite tĩnh, kết hợp với một số hiệu ứng đơn giản trong combat
<br/>
- Tồn tại những yếu tố tương tác, phản hồi input người chơi (vd: khi di chuột lên thẻ trong combat chúng sẽ nhô lên; nhiều yếu tố hiện lên thông tin bổ sung/miêu tả khi di chuột lên)
<br/>
<br/>


Sử dụng những ý tưởng và đồ hoạ từ Slay the Spire của Mega Crit: https://store.steampowered.com/app/646570/Slay_the_Spire/


### Một số nguồn đã tham khảo:


SDL:

dev.uet SDL image demo

dev.uet SDL event, keyboard

https://lazyfoo.net/tutorials/SDL/16_true_type_fonts/index.php

https://www.reddit.com/r/roguelikedev/comments/3snekfsdl2_performance_issues_a_possible_solution/

https://gamedev.stackexchange.com/questions/46238/rendering-multiline-text-with-sdl-ttf  
<br/>

static & extern:

https://youtu.be/1xY0rF399j0?si=jlY8bFyzVxQfs_8R

https://youtu.be/V-BFlMrBtqQ?si=c5nMbfJuE0SCIazv

https://www.geeksforgeeks.org/static-keyword-cpp/

https://stackoverflow.com/questions/10422034/when-to-use-extern-in-c  
<br/>

Inheritence:

https://youtu.be/X8nYM8wdNRE?si=RiijG-8GpksXrBsk

https://www.geeksforgeeks.org/inheritance-in-c/  
<br/>

enum:

https://www.geeksforgeeks.org/enumeration-in-cpp/

https://youtu.be/Fqn4pSRH6Ec?si=nHrA08rbwuc8kXFS  
<br/>

std::function:

https://youtu.be/DNp7fo226Qg?si=4e91pgHXn3B27ScY

https://www.geeksforgeeks.org/cpp-map-of-functions/

https://www.geeksforgeeks.org/std-function-in-cpp/  
<br/>

Forward declaration:

https://www.geeksforgeeks.org/what-are-forward-declarations-in-c/  
<br/>

Shuffle vector & true random:

https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector

https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
