안녕하십니까? 네온의 제작을 맡은 팀 타임리스의 마일스톤 0 시작하겠습니다.
Hello, let's start Teamless's MileStone 0 presentation.
Our game name is NEON


Our Team member has
Producer minseok kim,
Technical Leader sungwon baek,
Design Leader seulbin seo,
Test leader hyojoon kim,
Level designer junseong park


팀 타임리스는
프로듀서인 민석김
테크니컬 리더인 성원백
디자인 리더인 슬빈서
테스트 리더인 효준김
레벨 디자이너인 준성박
으로 구성돼 있습니다.


저희의 게임 컨셉을 가장 잘 나타내는 엘레베이터 피치로는
Only rely on the neon sign marked on the tile to escape
으로 정하게 되었고, 이제부터 그 게임 컨셉에 어울리는 기본 컨셉을 보여드리려고 합니다.

We think our team's best elevator pitch is
"Only rely on the neon sign marked on the tile to escape"


Now we show our game concept.
Let's see a brief video.

As you can see video,
The starting point of the player has been placed in the center for easily explain. This will be revised later.
If you look video carefully, you can see a some notification at the edge of the screen that the player is viewing.
This alarm tells to player, that the pattern tiles of that color will come from that direction.
After this alarm, the pattern tile is passed, and that pattern tiles leaving a afterimage where the pattern tile was passed.
And the player can avoid this pattern tile by jumping by using space bar.
There is not in video, but using this pattern tile's afterimage, the player can figure out which tile we can move or not.
And than the player can move to goal point using the arrow keys.
When the player is moving, the camera will move together, so that player can see our whole map.
This will be easily used at more huge stage.
And there is some kind of coin, the player can collect this coin.
This coin is used for score in the final stage.
However, later players can also use this coin to purchase some ability to help the stage.
If player use this coin for ability, the final score is low.


잠시 짧은 영상을 보고 가도록 하겠습니다.
플레이어의 시작지점은 직관적인 설명을 위해 중앙으로 위치를 했는데, 후 실 게임 개발 시에는 플레이어는 다른 지점에서 시작하게 될 것입니다.
영상을 자세히 보시면 플레이어가 보는 화면 끝 가장자리 부분에 잠시 후 이쪽 방향에서 이 색깔의 패턴타일이 올 것임을 알려주는 알림이 나타납니다.
일정 알림이 나타난 후, 패턴 타일이 지나가며, 패턴 타일이 지나간 자리에는 뒤에 나타나는 잔상의 효과가 나타날 것입니다.
그리고 플레이어는 패턴타일이 오는 타이밍에 맞춰 스페이스바를 누르게 되면, 점프하게 되어 패턴타일을 피하게 될 것입니다.
영상에는 없지만, 이 잔상의 효과를 이용해 플레이어는 자신의 지나갈 수 있는 타일을 파악하게 될 예정이며, 그렇게 파악한 타일을 이용하여 목적지까지 도달해야합니다.
그 후 플레이어는 방향키를 이용하여 골인지점까지 이동하게 되며, 플레이어가 이동함에 따라 카메라가 일정하게 움직이며 맵 전체를 보여주게 될 것입니다.
이는 더 넓어진 스테이지를 플레이어가 더 직관적으로 보기위해 이용될 것이다.
그리고 맵 곳곳에 배치된 코인은 유저가 수집할 수 있는 오브젝트인데, 수집한 갯수를 기반으로 최종적인 스코어를 계산해 낼 것이며, 혹은 이를 이용하여 추후 개발될 상점기능에 추가될 스테이지에 도움이 될 능력이나 아이템을 살 수 있는 용도로 쓰일 수 있도록 개발할 예정이다.


We chose 3 features of this game.

First, Through Sprite rotation or sprite scaling, it can inform to player more intuitively of pattern tiles situation.
Second, Through Multiple levels or environments, it can give sense of tension and speed to player with more complex and faster pattern tiles.
Last, Through file parsing for game content, it can give us to more easily use memory, and also later player can easily make their own stage. 





프로젝트 특징으로는 크게 3가지를 꼽았는데,

첫째로 스프라이트의 회전과 스케일링 과정을 통해, 플레이어에게 조금 더 직관적으로 현재의 패턴타일의 상황을 알려줄 수 있을 것 이고.

둘째로 여러 레벨과 패턴들이 생성되는 과정을 통해, 단순한 패턴으로 인해 플레이어가 지루해 질 때쯤, 더 복잡하고 더 빠른 패턴들이 등장해, 조금 더 긴장감과 속도감을 불어넣어 유저들이 재미를 느끼게 할 것이다.

마지막으로 스테이지가 증가함에 따라 커지는 맵 규모와 많아지는 패턴타일들의 모든 것들을 코드 내부에 담게 되면 용량이 비약적으로 커지기 때문에 모든 스테이지들을 외부에서 불러와 게임 내부에서 읽음으로써 더 많은 메모리를 확보하여 추후에 플레이어들이 스테이지를 제작함에 있어서도 편리하다고 판단했다.


The most important risk of our game is 'level design' and 'algorithm for moving pattern tiles'.
At first, as we develop 'level design', we will try to find some kind of formula or rules that can easily and automatically make stage.
Also, as we develop pattern tiles movement, we will try to find some formula or try to use some kind of best algorithm to easily manage our game's pattern tiles.


가장 중요하게 생각되는 리스크들은 레벨 디자인과 보다 빠른 패턴타일의 진행 연산으로 생각되는데,


As we develop 'level design', we will try to find some kind of formula or rules that can easy and automatically to make stage.
레벨 디자인은 일단 개발을 하면서 하나하나 맞추는 과정 속에서, 정해진 수식을 계산하고 도출해 내 자동적으로 레벨이 어렵지 않게 증가하도록 할 것이며, 패턴의 진행방향 역시 처음엔 일일히 변수값을 증가시키는 것에서, 여러 탐색 알고리즘들 중 가장 적합하고 가장 빠르다고 판단되는 알고리즘을 찾아 적용시켜 패턴들이 자동적으로 이동하게 만들예정이다.



===============================================================================


저희 게임에서 가장 주목되어야 할 부분은 이 타일의 구성에 있습니다.
타일은 2가지 타입의 상태(빛 ON, OFF)를 가지며 필요한 모양을 갖추기 위한 포지션에 대한 정보를 가집니다.
이러한 형태와 역할을 갖는 타일을 만들기 위해 저희는 2차원 배열을 사용한 노드를 만들기로 계획하였습니다.
이러한 노드들은 각 주변의 노드들과 유기적인 연결관계를 가지며
각자 현재의 타입과 현재의 포지션, 주변 노드들의 정보를 플레이어의 유닛에 전달하는 기능을 합니다

예를들어 현재 유저의 유닛이 그림에 있는[0,0] 순번의 노드에게 정보를 받아 올 경우 이 노드의 포지션을 받아와 유닛의 포지션이 이 위에 겹치게 되고,
유닛이 이 노드의 타입을 인식하여 노드가 발광중인 타입이라면 체력을 잃게되고 유닛의 포지션이 스테이지 처음의 위치로 초기화됩니다.
또한 이 노드들은 상하좌우에 있느 주변 노드들의 정보를 갖고 있기 때문에 유저가 간단하게 방향키를 조작하는것 만으로 주변 노드들의 정보를 받아와
유닛의 포지션을 수정하고 유닛이 이동한 노드의 정보를 받아오게 합니다. 

또한 노드의 생성과 노드가 가질 모든 값들의 변수는 전부 텍스트파일에 정리되어 최대한 깔끔하고 가시성이 좋은 코드를 작성하려 계획중에 있습니다.



2차원 배열을 사용한 노드를 만들어 그 노드들에 현재의 상태(발광 o,x),  노드의 위치 등의 데이터를 갖도록 만든다.
각 노드들의 생성, 포지션 , 패턴을 위한 현재의 상태 등을 모두 텍스트의 값으로 저장하고 상태의 변화를 통제 할 것이다.







일단 이 게임을 보는 순간 저희가 왜 네온으로 콘셉트를 잡았는지 궁금하실 수 있다고 생각을 합니다. 정하게 된 과정을 설명하자면 저희가 게임을 개발하기 전 여러 게임들을 찾아보았고 “System Purge “라는 게임을 통해 여러가지 아이디어가 나왔습니다. 지금은 물론 이 게임과 완전히 다른 게임입니다. 그리고 우리는 스테이지가 증가할수록 어려워지는 패턴 장애물을 설치하기로 하였고 뷰는 Top view로 구성하기로 하였습니다. 이를 확실하게 잘 알려줄 수 있는 컨셉으로 네온이 나왔고, 이 네온을 통해 좀 더 장애물을 사실적으로 나타낼 수 있으며 네온이 빛이라는 성질을 잘 이용하려고 하였습니다. 그 중 하나가 잔상을 통해 더 많고 다양한 게임 아이템이 나올 수 있다는 것을 알게 되었습니다. 예를 들어 지금 자료는 없지만 추후 높은 레벨이 만들어진다면 네온이 지나간 잔상으로 인해 길을 알 수 있도록 계획할 예정입니다. 이러한 이유들로 저희는 네온으로 결정을 하였고, 이 컨셉을 정한 후, 우리는 어울리고 더 신나는 게임을 만들기 위해 8비트 음악을 깔기로 결정하였습니다. 그리하여 저희의 아트 컨셉은 네온과 8비트 음악을 기반으로 개발하기로 하였습니다.





먼저 우리 팀의 개발 과정에 도움이 되기 위해서 팀원 모두가 c++코어 가이드라인을 준수하여 코딩을 하는지 체크할 것입니다. 저는 GAM150 프로젝트 과정에서 각 팀원이 서로 다른 스타일로 변수 이름과 함수명을 정해놓은것 때문에 서로가 각자의 코드를 이해하는데 많은 시간이 소요되었습니다. 
이번 프로젝트 과정에서는 이러한 혼란을 미연에 방지하기 위해 처음 코드를 작성할때 부터 가이드라인을 준수하는지 확인할 것입니다. 
이것은 서로의 깃 브랜치를 병합하는 과정에서 발생하는 오류의 빈도도 줄여줄 것입니다.

두번째로, 게임 개발 효율성을 높이기 위해서 레벨 디자인 에디터를 개발할 것입니다.  이것은 각 스테이지를 GUI를 이용해 손쉽게 맵의 크기를 결정하고 플레이어의 시작위치와 골인지점, 코인들을 배치할 수 있을것입니다. 이 툴은 우리 팀의 레벨 디자이너가 각 스테이지의 밸런스를 조정하는데 걸리는 시간을 큰 폭으로 줄여줄 것입니다.
