- Cách chạy: cho tệp 'assets' vào tệp 'bin' rồi chạy cc.exe
# I. Giải thích một số khái niệm, tính năng chính:
*Mọi thao tác đều bằng chuột*

## Thẻ, người chơi và quái
### Thẻ:
- Để sử dụng thẻ, cần có đủ năng lượng
- 3 loại thẻ chính:
  + Attack: Dùng để tác động vào quái
  + Skill: Dùng lên nhân vật, để buff hoặc tạo Khiên
  + Power: Dùng lên nhân vật, để buff, chỉ được sử dụng 1 lần và sẽ biến mất khỏi combat
![anger](https://github.com/user-attachments/assets/c955634e-91f0-4e9e-891b-da1e452d0987)

- Từ khoá đặc biệt:
  + Exhaust: Sau khi sử dụng sẽ biến mất khỏi combat <br/>
![anger (1)](https://github.com/user-attachments/assets/cf35087b-851c-478c-927f-02ba313af399)

### Nhân vật:
- Những số liệu chính: vàng, máu, khiên, năng lượng trong combat, các status
![image](https://github.com/user-attachments/assets/936d0ea5-53a4-4d4a-9980-652ba72013da)

- Resources bộ thẻ, vật phẩm<br/>
  *Thẻ và vật phẩm có 3 độ hiếm Common, Uncommon và Rare*
  + Vật phẩm: Resource được thực hiện khi một điều kiện nào đó thoả mãn
  ![image](https://github.com/user-attachments/assets/ce649fc2-539b-4ccb-8be4-a4af1c5ee35e)

- Máu của nhân vật giữ nguyên sau mỗi combat (không tự hồi), khiên sẽ mất đi khi kết thúc lượt
### Quái:
- Những số liệu chính: máu, khiên, các status
- Hành động của quái sẽ được chọn ngẫu nhiên (hoặc có qui luật) từ một vector các hành động, mỗi quái có một vector riêng, quái không sử dụng thực hiện liên tiếp một hành động quá nhiều lần
  + Hành động có thể bao gồm: tấn công, buff, debuff, tác động vào nhân vật, tác động vào bộ thẻ (tạm thời hoặc cố định),...
  ![image](https://github.com/user-attachments/assets/4728638e-a0e5-4537-a557-f4682c7423f9)

<br/>
* Cả Nhân vật và quái đều có các debuff, buff được lưu trong map<statusId, Status> statuses với 'level' mặc định = 0, một khi level > 0, hiệu ứng của status sẽ kích hoạt, thường là những thay đổi về số liệu (vd: tăng 25% damage nhận được trong hàm take_damage() bằng cách nhân damage nhận được với 1.25)
<br/>

## Map:
+ Một khi bắt đầu game, một map sẽ được tạo ra với những node(điểm) được nối vào nhau
+ Map có dạng tương đương mảng 2D, và luôn có 20 'hàng' và 5 'cột', mỗi ô chứa nhiều nhất một node
  - Người chơi chỉ có thể đi những điểm có đường nối với điểm hiện tại, có thể nhìn, quyết định trước đường đi

### Có 5 loại node chính:
<a id="combat"></a>
**1, Combat**

*Combat diễn ra theo lượt, lượt chắn là lượt người chơi, lượt lẻ là lượt quái:*
+ Lượt người chơi:
  - Người chơi chọn những thẻ phù hợp (nếu đủ năng lượng) để tránh mất máu, thắng combat hiệu quả
  - Vòng lặp quản lý thẻ: Trong combat, thẻ của người chơi di động giữa 3 'hộp' - hộp bốc thẻ(Draw pile), hộp cất thẻ(Discard pile), và 'Tay' người chơi:
    * Bắt đầu lượt chơi, 5 thẻ ngẫu nhiên được đẩy từ Draw pile vào Tay người chơi, sau khi sử dụng một thẻ, nó sẽ bị đẩy vào Discard pile 
    * Một khi kết thúc lượt, những thẻ còn lại chưa được sử dụng sẽ bị đẩy vào Discard pile
    * Một khi Draw pile hết thẻ, tất cả thẻ trong discard pile sẽ được đẩy vào draw pile
    **Như đã nêu trên, một số loại thẻ (thẻ Power, thẻ có từ khoá Exhaust,...) sẽ không bị đẩy vào Discard pile sau khi sử dụng -> mất khỏi vòng lặp combat*
  <a id="intent"></a>
  - Đồng thời, tất cả quái sẽ chọn trước và biểu hiện (bằng một ảnh minh hoạ và một phần miêu tả ngắn) một hành động để thực hiện vào lượt tiếp theo, người chơi có thể giựa vào thông tin này để phán ứng (vd: quái định tấn công thì người chơi sẽ tạo Khiên)
+ Lượt quái:
  - Thực hiện hành động đã chọn trong lượt của người chơi
+ Sau khi thắng combat, người chơi nhận 3 phần thưởng: vàng, 1 trong 2 vật phẩm và 1 trong 3 thẻ bài
  - *Người chơi nên lựa chọn thẻ phù hợp (hoặc bỏ qua nếu không có thẻ phù hợp) để trong các combat tiếp theo, mỗi khi bắt đầu lượt, không random vào những thẻ cộng hưởng kém với các thẻ khác* 
<br/>

**2, Shop:** Sử dụng vàng để mua thẻ và vật phẩm, hoặc sử dụng 75 vàng để xoá một thẻ khỏi bộ thẻ
*Người chơi nên lựa chọn thẻ phù hợp*
<br/>

**3, Event:** Những Sự kiện có tính tương tác (vd: người chơi chọn một thẻ để xoá/copy, đổi một thẻ để hồi máu, đổi vàng để hồi máu,...*(hiện tại game chưa có nhiều Sự kiện khác nhau)*)
<br/>

**4, Treasure:** Người chơi nhận vàng và 1 trong 2 vật phẩm (sử dụng chung yếu tố phần thưởng của combat)
<br/>

**5, Rest:** Hồi một % máu cho nhân vật
<br/>

**Những phần thưởng từ Combat, Chop hay Treasure có độ hiếm khác nhau, mỗi thẻ có thể sở hữu vô số, riêng vật phẩm mỗi loại chỉ có 1 (sau khi nhận được sẽ bị erase khỏi std::set các vật phẩm)*

<br/>

## Đồ hoạ:
- Đồ hoạ thô sơ với các sprite tĩnh, kết hợp với một số hiệu ứng đơn giản trong combat khi các đối tượng tác động lên nhau
- Tồn tại những yếu tố tương tác, phản hồi input người chơi (vd: khi di chuột lên thẻ trong combat chúng sẽ nhô lên, nhiều thể hiện thông tin bổ sung khi di chuột lên,...)
<br/>



# II. Cấu trúc:
## **Class Game:** 
*Class thực hiện những công việc vĩ mô của game, gồm: <br/>*
**1, Bộ phận tạo cửa sổ:**
- Những file liên quan:
  + draw/window.cpp
  + game.cpp
- Viết theo tài liệu hướng dẫn

**2, Bộ phận render ảnh, chử TTF:**
**Đây là những hàm thực hiện mọi nhiệm vụ display mọi sprite, chữ, miêu tả trong game*
- Những file liên quan:
  + draw/img_renderer.cpp: Hàm cốt lõi render_img thực hiện việc load texture và gọi SDL_RenderCopy()
  + draw/text.cpp: Hàm render_text thực hiện việc load phông chư, và load texture chữ và gọi SDL_RenderCopy()
- Mọi Font và Texture một khi tạo ra sẽ được lưu vào std::map tương ứng (Game::textureMap, Game::textTextureMap, Game::fontMap) với key (thường là tên file của ảnh), mọi lần render tiếp theo sẽ sử dụng lại texture được lưu trong những std::map nay để tránh render lại

**3, Bộ phận quản lí input chuột:**
- Những file liên quan:
  + input/input_manager.cpp: Xử lí những input click chuột trái, nhấc chuột trái, sử dụng con lăn; cập nhật những biến tương ứng trong mouse_input.cpp để các thành phần khác sử dụng
  + input/mouse_input.cpp: Khởi tạo những biến vị trí chuột, bool kiểm tra click
 
**4, Bộ phận thực hiện logic game:**
- Những file liên quan:
  + game.cpp: Ngoài ra, logic chạy phần mềm game bao gồm các hàm clear_renderer(), present_renderer() để render đồ hoạ, và hàm update()
- Hàm update() thực hiện việc thể hiện trạng thái state hiện tại của game (dựa vào Game::gameState) (vd: ở menu Start game thì hàm gọi display_start_menu(), trong combat thì hàm gọi display_combat(),...)


## **Class Gui:** 
Lớp phụ huynh của tất cả yếu tố giao diện, kết hợp với class Game để render ảnh
- Những file liên quan:
  + gui/gui.cpp: Định nghĩa sẵn hitbox SDL_Rect và các hàm kiểm tra vị trí, click chuột để các class con sử dụng
<br/>

### *Đa số những yếu tố trong quá trình chơi sẽ được khởi tạo bằng cách key + map để gán các giá trị/tính chất hiệu quả, code nhìn gọn gàng, tránh phải viết hàm if else riêng để định nghĩa các object*
❕Những yếu tố khởi tạo bằng phương pháp này bao gồm:
- *Các hiệu ứng, giá trị của thẻ*
- *Các vật phẩm Relic của Character, status của các đối tượng*
- *Enemy, các hành động của Enemy (được gọi là intent trong code)
- *Các Event* <br/>

**Quy trình khởi tạo chung:**
- *Những yếu tố trên sẽ có một biến Struct attributes*
  + *Những biến này sẽ thường chứa những số liệu, giá trị int, bool đặc trưng của yếu tố, và các string chứa tên file sprite, phần mô tả(nếu có)*
- *Hàm khởi tạo nhận vào một id (dạng enum), rồi gán những giá trị tương ứng từ các map<id, Attributes> attriMap, rồi gán: attributes = attriMap.at(id) bằng phương pháp aggregate list initialization*

## **Yếu tố thẻ, bộ thẻ:** <br/>
Những file liên quan:<br/>
**1, Class Deck:<br/>**
*Mọi tương tác với bộ thẻ sẽ được thực hiện lên biến global Deck deck, được khởi tạo trong main.cpp*
+ cards/deck.cpp: khởi tạo, reset các biến, vector, đồng thời quản lý vector Inventory
  - vector<CardId> Deck::idInventory\: dùng để ghi lại những thẻ mà người chơi sở hữu, khi thẻ được thêm vào inventory hàm add_card() sẽ được gọi để push_back id của thẻ đó
  - vector<Card> Deck::inventory\: sự dụng ngoài combat để check thẻ, khởi tạo thẻ với id từ idInventory
+ cards/deck_combat.cpp:
  - Thực hiện khởi tạo và bố trí các vector hộp thẻ Draw Pile, Discard Pile, Hand, bằng các thao tác push_back() và erase() cơ bản, như đã [miêu tả ở phần II](#combat)
  - Sử lý input của người chơi chọn thẻ, sử dụng thẻ, với dòng hoạt động sau:
      * hand_process() display các thẻ trên tay và gọi interact_cards()
      * interact_cards() xử lý thao tác chọn thẻ, cập nhật vị trí của thẻ đang được chon vào selectedIdx
      * sau khi đã chọn một thẻ, interact_cards() gọi query_and_activate_process() đợi input của người chơi chọn mục tiêu hợp lệ rồi thực hiện hiệu ứng của thẻ lên mục tiêu đó
**2, Class Card:**
+ cards/id_to_card.cpp: Định nghĩa cAttriMap, attributes của thẻ gồm: năng lượng (cost), loại thẻ [link], bool kiểm tra từ khoá Exhaust và Ethereal, tên file sprite, hàm thực hiện hiệu ứng (dưới dạng một std::function)
+ cards/card.cpp:
  - Những hàm display(), hàm highlight thực hiện làm cho thẻ nhô lên khi di chuột lên thẻ
  - query_targetE() & query_targetC(): được gọi trong Deck::query_and_activate_process() đối với thẻ đã được chọn, đợi người chơi click chuột vào mục tiêu (là Character hoặc Enemy tuỳ vào hiệu ứng của thẻ), và trả về vị trí của mục tiêu (vị trí của người chơi mặc định = 0)
  - activate(): luôn nhận vào vector stageEnemies (nhưng chỉ sử dụng nếu mục tiêu của thẻ là quái), và vị trí của mục tiêu đã chọn, rồi thực hiện hiệu ứng trong std::function attributes.action (được định nghĩa khi khởi tạo dựa vào id của thẻ) 


## **Character và Enemy:** <br/>
Những file liên quan:<br/>
**1, Character:** <br/>
*Mọi tương tác với nhân vật sẽ được thực hiện lên biến global Character ironclad, được khởi tạo trong main.cpp*
+ character/character.cpp:
  - Những hàm reset các biến, vector của nhân vật
  - Những hàm display cơ bản, display năng lượng hiện tại của nhân vật,...
    + Máu và khiên thể hiện bằng một hình chữ nhật có độ dài là tỉ lệ của máu hiện tại với máu tối đa
  - Những hàm thực hiện các phép tính khi nhân vật mất máu, hồi máu, tạo khiên,...
    + Hàm take_damage() khởi tạo những object hiệu ứng vào một vector khi nhân vật mất máu
+ character/relics.cpp:
  - Định nghĩa relAttriMap gồm: tên vật phẩm, std::function thực hiện hiệu ứng (nếu cần), mô tả điều kiện kích hoạt và hiệu ứng
  - Những hàm display các relic đã có ở một thanh ở mép trên màn hình, hàm hiện thông tin, mô tả khi di chuột lên
gộp những cái mà trùng điều kiện kích hoạt
+ character/relics_inventory.cpp:
  - Hàm check người chơi có sở hữu một relic cụ thể không
  - Những hàm kiểm tra điều kiện kích hoạt của relic (đối với những relic trùng điều kiện kích hoạt; còn lại sẽ check điều kiện riêng ở đoạn code phù hợp (vd: một relic kích hoạt khi quái chết sẽ có một dòng check ở trong enemy_process() trong Game::display_combat() của file combat/combat.cpp vì đây là hàm xử lí trường hợp quái chết))
+ character/statuses.cpp:
  - Quản lý các status được định nghĩa trong conditions.h, display, và giảm level-- sau khi kết thúc lượt nếu cần

**2, Enemy:**
+ enemies/id_to_enemy.cpp: Định nghĩa eAttriMap, các attributes gồm: kích thước, máu, atk, tên file sprite, những vector hành động, 'thuật toán' chọn hành động từ những vector đó
  - Những vector hành động bao gồm: tỉ lể random ra hành động, số lần đã sử dụng liên tiếp một hành động (mặc định là 0 khi khởi tạo), số lần sử dụng liên tiếp tối đa, std::function hành động và đồ hoạ [intent]("intent") của hành động đó
  - Những quái cơ bản thường chỉ có một vector hành động, và hàm thuật toán gọi một hàm chọn random một hành động (nếu random phải một hành động có số lần đã sử dụng liên tiếp một hành động == số lần sử dụng liên tiếp tối đa, thì random lại cho đến khi ra hành động khác); quái phức tạp hơn có thể random giữa các vector khác nhau, hoặc thực hiện các hành động cố định dựa vào int turn
+ enemies/intent.cpp:
  - Định nghĩa class Intent, yếu tố đồ hoạ thể hiện hành động tiếp theo của quái
  - Định nghĩa intentAttriMap gồm: tên file sprite, mô tả
+ enemies/enemy.cpp:
  - Hàm generate intent sử dụng thuật toán đã gán để chọn một hành động rồi lưu vào biến std::function Enemy intended
  - Các hàm còn lại tương tự Character

### Các game state
**0, Map cây và các node**
- states/map/nodes.cpp:
  + Hàm khởi tạo node gồm loại node và id: id của node = level*10 + pos (level: dòng, pos: cột), mỗi node sẽ chứa id của các node trước trong vector<id> prev, và sau trong vector<int> next có đường nối với nó, và sử dụng id để look up các object node cụ thể trong nodeMap khi cần (không sử dụng con trỏ để tránh bug)
  + Khi detect_click(), node thực hiện đổi Game::gameState thành state tương ứng loại node
- states/map/tree.cpp;
  + Thực hiện việc vẽ và display, quản lý các node hợp lệ, push_back id của node vừa chọn vào vector<int> playerPath, chỉ cho phép người chơi chọn node có playerPath.back() trong vector prev của nó (có đường nối)
  + Hàm generate_path(): random ra một con đường từ level 0 (dòng 0 từ dưới lên) đến level 20, mỗi level, random ra một vị trí cột sao cho abs(*cột tiếp theo* - *cột hiện tại*) không lớn hơn 1, và random Loại của node (trừ một số tầng sẽ cố định một loại node (vd: level 19 luôn là một node Rest)); với mỗi node tạo ra, thêm nó vào nodeMap với key là id, trước khi tạo ra; nếu vị trí tiếp theo đã tồn tại trước một node từ một lần gọi generate_path() trước, không thêm node mới, nhưng thêm node hiện tại vào vector prev của node tiếp theo đó (tạo ra nhiều đường nối đến cùng 1 node)

**1, Combat**
- states/combat/combat_ui.cpp: Khởi tạo nút kết thục lượt, nút display Draw pile, Discard pile
- states/combat/combat.cpp:
  + Cách chọn đội hình quái: chọn vector từ vector<vector<vector<Enemy>>> formation từ 0 đến 2 dựa vào độ khó của combat (thể hiện quả ảnh của node), và chọn random một trong những vector trong vector đó
  + Dòng hoạt động: Khởi tạo combat, xử lí trường hợp quái chết, người chơi chết, người chơi thắng xử lí lượt của nhân vật và quái
- states/combat/rewards.cpp:
  + Hàm generate_items() random ra random int vàng (cReward), những vật phẩm (rReward), thẻ (ccReward) với độ hiếm phụ thuộc vào những biến UncomThres và RareThres (hàm rand một int value thuộc khoảng 0 đến 9, vd: nếu value >= UncomThres thì sẽ khởi tạo một thẻ/relic bất kì thuộc uncommonCardPool/uncommonRelicPool trong pools/pools.cpp)
  + Biến used của mỗi phần thưởng ghi lại trạng thái của các phần thưởng, sau khi đã nhận hết và cả 2/3 biến used == true, combat kết thúc và Game::gameState trở về map
  + Đối với relic, một khi được chọn (kể cả khi mua từ Shop), đặt bool active của relic đó trong *map<relicId, Relic> Character::relicInv*, sẽ bị erase khỏi set các relic(bản sao) (set relic gốc vẫn giữ nguyên cho những lần chơi khác) 
 
**2, Treasure**
- states/treasure/treasure.cpp: Sử dụng lại những class và hàm tạo phần thưởng từ states/combat/rewards.cpp + hàm display hòm kho báu

**3, Shop **
- states/shop/shop_generation.cpp: Logic random thẻ và vật phẩm tương tự generate_items() + quyết định giá dựa trên độ hiếm
- states/shop/shop.cpp: Display shop, giá của các item, xử lí logic mua item, xoá đi sau khi mua

**4, Event**
- states/event/id_to_event.cpp: <sub> Logic của phần code này còn kém hiệu quả </sub>
  + Các lựa chọn: Khởi tạo từ choiceAttriMap, attributes gồm: số lần chọn cho phép, tên của lựa chọn, std::function<bool> mở ra menu để thao tác nếu có (vd: mở Deck::inventory, dợi người chơi chọn 1 thẻ để xoá,...) trả về true sau khi thao tác xong
  + Event: Mọi lần chọn node event sẽ random một eventId id, rồi khởi tạo Event từ evAttriMap, attributes gồm: tên file ảnh minh hoạ, tên Event, miêu tả Event, vector các Choice
- states/event/event.cpp: Thực hiện random ra event trong hàm Event::generate(), display Event và các Choice, xử lí input và các menu nếu có  

**5, Rest**
- states/rest/rest.cpp: display và xử lí input đối với nút hồi máu

**Những yếu tố phụ:** <br/>
*Top Panel: gui/top_panel.cpp:* Thanh ở mép trên màn hình, hiện máu của nhân vật, vàng của nhân vật và một nút display Deck::inventory có thể dùng khi ở ngoài combat <br/>
*Hiệu ứng: gui/fx/fx.cpp:* Display những hiệu ứng số dmg, vệt trắng khi đối tượng mất máu, ngoài toạ độ vị trí x, y, các hàm display hiệu ứng dựa vào int t (biến đếm frame hiện tại) để thay đổi vị trí và kích thước của các ảnh, chữ bằng phương trình bậc 1 / 2; ngoài ra những hàm này nhận vào int delay (trừ vào t) để 'tách rời' các object hiệu ứng khởi tạo cùng lúc để không bị chồng lên nhau 
<br/>
<br/>

# III. Video giới thiệu thành phần chính, combat: https://drive.google.com/drive/u/1/folders/1G5FoDcMxB9hbUa_ScpKciqVE-psHi4pG

# IV. Một số nguồn đã tham khảo:
## **1, Công nhận:** Sử dụng những ý tưởng và đồ hoạ từ Slay the Spire của Mega Crit: https://store.steampowered.com/app/646570/Slay_the_Spire <br/>

## **2, Learnings:** 

### Các khái niệm và kĩ thuật lập trình:
**SDL:**

- dev.uet SDL image demo

- dev.uet SDL event, keyboard

- https://lazyfoo.net/tutorials/SDL/16_true_type_fonts/index.php

- https://www.reddit.com/r/roguelikedev/comments/3snekfsdl2_performance_issues_a_possible_solution/

- https://gamedev.stackexchange.com/questions/46238/rendering-multiline-text-with-sdl-ttf  
<br/>

**static & extern:**

- https://youtu.be/1xY0rF399j0?si=jlY8bFyzVxQfs_8R

- https://youtu.be/V-BFlMrBtqQ?si=c5nMbfJuE0SCIazv

- https://www.geeksforgeeks.org/static-keyword-cpp/

- https://stackoverflow.com/questions/10422034/when-to-use-extern-in-c  
<br/>

**Inheritence:**

- https://youtu.be/X8nYM8wdNRE?si=RiijG-8GpksXrBsk

- https://www.geeksforgeeks.org/inheritance-in-c/  
<br/>

**enum:**

- https://www.geeksforgeeks.org/enumeration-in-cpp/

- https://youtu.be/Fqn4pSRH6Ec?si=nHrA08rbwuc8kXFS  
<br/>

**std::function:**

- https://youtu.be/DNp7fo226Qg?si=4e91pgHXn3B27ScY

- https://www.geeksforgeeks.org/cpp-map-of-functions/

- https://www.geeksforgeeks.org/std-function-in-cpp/  
<br/>

**Forward declaration:**

- https://www.geeksforgeeks.org/what-are-forward-declarations-in-c/  
<br/>

Shuffle vector & true random:

- https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector

- https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
