# RosettaStone

<img src="./Medias/Logos/Logo.png" width=256 height=256 />

[![License](https://img.shields.io/badge/Licence-AGPLv3-blue.svg)](https://github.com/utilForever/RosettaStone/blob/main/LICENSE) ![Windows](https://github.com/utilForever/RosettaStone/workflows/Windows/badge.svg) ![Ubuntu](https://github.com/utilForever/RosettaStone/workflows/Ubuntu/badge.svg) ![macOS](https://github.com/utilForever/RosettaStone/workflows/macOS/badge.svg) ![Ubuntu - Codecov](https://github.com/utilForever/RosettaStone/workflows/Ubuntu%20-%20Codecov/badge.svg) [![Build Status](https://travis-ci.com/utilForever/RosettaStone.svg?branch=main)](https://travis-ci.com/utilForever/RosettaStone)

[![codecov](https://codecov.io/gh/utilForever/RosettaStone/branch/main/graph/badge.svg)](https://codecov.io/gh/utilForever/RosettaStone)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/df6a02e1358f4e719e7bebb9a728d2ab)](https://www.codacy.com/app/utilForever/RosettaStone?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=utilForever/RosettaStone&amp;utm_campaign=Badge_Grade)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/utilForever/RosettaStone.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/utilForever/RosettaStone/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/utilForever/RosettaStone.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/utilForever/RosettaStone/context:cpp)
[![CodeFactor](https://www.codefactor.io/repository/github/utilforever/RosettaStone/badge)](https://www.codefactor.io/repository/github/utilforever/RosettaStone) [![Discord](https://img.shields.io/discord/483192043737186335.svg)](https://discord.gg/6R3UueR)

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=RosettaStone&metric=alert_status)](https://sonarcloud.io/dashboard?id=RosettaStone) [![Lines of Code](https://sonarcloud.io/api/project_badges/measure?project=RosettaStone&metric=ncloc)](https://sonarcloud.io/dashboard?id=RosettaStone) [![Maintainability Rating](https://sonarcloud.io/api/project_badges/measure?project=RosettaStone&metric=sqale_rating)](https://sonarcloud.io/dashboard?id=RosettaStone) [![Reliability Rating](https://sonarcloud.io/api/project_badges/measure?project=RosettaStone&metric=reliability_rating)](https://sonarcloud.io/dashboard?id=RosettaStone) [![Security Rating](https://sonarcloud.io/api/project_badges/measure?project=RosettaStone&metric=security_rating)](https://sonarcloud.io/dashboard?id=RosettaStone)

RosettaStone is Hearthstone simulator using C++ with some reinforcement learning. The code is built on C++17 and can be compiled with commonly available compilers such as g++, clang++, or Microsoft Visual Studio. RosettaStone currently supports macOS (10.14 or later), Ubuntu (18.04 or later), Windows (Visual Studio 2017 or later), and Windows Subsystem for Linux (WSL). Other untested platforms that support C++17 also should be able to build RosettaStone.

## Related Repositories

  * [RosettaStone GUI](https://www.github.com/utilforever/RosettaStone-GUI)

## Key Features

  * C++17 based Hearthstone library
  * Console and GUI simulator program
  * C++ and Python API

## To-do Features

  * Upgrade "The Innkeeper" to smart
  * Recommend top-tier decks
  * Deck tracker
  * Web simulator

## Cards Implementation

### Standard Format

  * 97% Core Set (230 of 235 cards)
  * 60% Ashes of Outland (81 of 135 cards)
  * 57% Scholomance Academy (78 of 135 cards)
  * 46% Madness at the Darkmoon Faire (79 of 170 cards)
  * 80% Forged in the Barrens (136 of 170 cards)
  * 1% United in Stormwind (2 of 170 cards)
  * 0% Fractured in Alterac Valley (0 of 2 cards)

### Wild Format

  * **100% Legacy (167 of 167 Cards)**
  * **100% Expert1 (245 of 245 Cards)**
  * **100% Demon Hunter Initiate (20 of 20 Cards)**
  * 13% Curse of Naxxramas (4 of 30 Cards)
  * 5% Goblins vs Gnomes (7 of 123 Cards)
  * 3% Blackrock Mountain (1 of 31 Cards)
  * 6% The Grand Tournament (8 of 132 Cards)
  * 6% The League of Explorers (3 of 45 Cards)
  * 2% Whispers of the Old Gods (4 of 134 Cards)
  * 11% One Night in Karazhan (5 of 45 Cards)
  * 0% Mean Streets of Gadgetzan (0 of 132 Cards)
  * 3% Journey to Un'Goro (5 of 135 Cards)
  * 3% Knights of the Frozen Throne (5 of 135 Cards)
  * 2% Kobolds & Catacombs (3 of 135 Cards)
  * 2% The Witchwood (3 of 135 Cards)
  * 2% The Boomsday Project (4 of 136 Cards)
  * 1% Rastakhan's Rumble (2 of 135 Cards)
  * **100% Rise of Shadows (136 of 136 cards)**
  * **99% Saviors of Uldum (134 of 135 cards)**
    * Except 'Zephrys the Great' (ULD_003)
  * **100% Descent of Dragons (140 of 140 cards)**
  * 57% Galakrond's Awakening (20 of 35 cards)

### Classic Format

  * 4% Vanilla Set (16 of 382 Cards)

## Implementation List

  * [Ability list](./Documents/AbilityList.md)
  * Card list
    * [Standard Format](./Documents/CardList%20-%20Standard.md)
    * [Wild Format](./Documents/CardList%20-%20Wild.md)
    * [Classic Format](./Documents/CardList%20-%20Classic.md)
  * [Task list](./Documents/TaskList.md)

## Quick Start

You will need CMake to build the code. If you're using Windows, you need Visual Studio 2017 in addition to CMake.

First, clone the code:

```
git clone https://github.com/utilForever/RosettaStone.git --recursive
cd RosettaStone
```

### Python API

Build and install the package by running

```
pip install -U .
```

**NOTE**: We are making Python API and related examples.

### C++ API

For macOS or Linux or Windows Subsystem for Linux (WSL):

```
mkdir build
cd build
cmake ..
make
```

For Windows:

```
mkdir build
cd build
cmake .. -G"Visual Studio 15 2017 Win64"
MSBuild RosettaStone.sln /p:Configuration=Release
```

Now run console simulator:

```
bin/RosettaConsole
```

**NOTE**: To run GUI simulator, please check out [RosettaStone GUI](https://www.github.com/utilforever/RosettaStone-GUI).

### Docker

```
docker pull utilforever/rosettastone:latest
```

Now run console simulator:

```
docker run -it utilforever/rosettastone
[inside docker container]
/app/build/bin/RosettaConsole
```

### More Instructions of Building the Code

To learn how to build, test, and install the SDK, please check out [Install.md](./Documents/Install.md).

## Documentation

All the documentations for the framework can be found from [the project website](https://utilforever.github.io/RosettaStone/) incluing the API reference.

## Presentations

  * [TFCON 2018 Poster Session](./Medias/Presentations/TFCON%202018%20-%20Hearthstone%2B%2B%2C%20Hearthstone%20Simulator%20with%20Reinforcement%20Learning.pdf)
  * [NDC 2019](./Medias/Presentations/NDC%202019%20-%20Development%20Process%20of%20Hearthstone%20Reinforcement%20Learning%20Environment%20(Korean).pdf)

## Videos
  
  * [NDC 2019](https://www.youtube.com/watch?v=yO9QRinXosE)

## Sprints

  * [PyCon Korea 2018 Sprint Session](https://archive.pycon.kr/2018/program/sprint/3)
  * [Sprint Seoul - April 2019](https://sprintseoul.org/)

## Articles

  * NDC 2019
    * [[NDC2019] 하스스톤을 위한 '알파고'를 만들 수는 없을까? - 인벤](http://www.inven.co.kr/webzine/news/?news=219330&site=hs)
    * [[NDC 19] '알파고' 같은 하스스톤 인공지능을 만들기 위한 험난한 여정 - 디스이즈게임](http://www.thisisgame.com/webzine/gameevent/nboard/227/?n=93644)
    * [[NDC2019 #11] 넥슨 프로그래머의 ‘하스스톤’ A·I 제작기 - 경향게임스](http://www.khgames.co.kr/news/articleView.html?idxno=118028)
    * [[NDC 2019] 넥슨 프로그래머의 ‘하스스톤’ AI 도전기 - OSEN](http://www.osen.co.kr/article/G1111130399)

## How To Contribute

Contributions are always welcome, either reporting issues/bugs or forking the repository and then issuing pull requests when you have completed some additional coding that you feel will be beneficial to the main project. If you are interested in contributing in a more dedicated capacity, then please check out [Contributing.md](./Documents/Contributing.md).

  * [Code of Conduct](./Documents/CodeOfConduct.md)
  * [Issues](./Documents/Issues.md)
    * [How to Contribute in Issues](./Documents/Issues.md#how-to-contribute-in-issues)
    * [Asking for General Help](./Documents/Issues.md#asking-for-general-help)
    * [Submitting a Bug Report](./Documents/Issues.md#submitting-a-bug-report)
    * [Triaging a Bug Report](./Documents/Issues.md#triaging-a-bug-report)
    * [Resolving a Bug Report](./Documents/Issues.md#resolving-a-bug-report)
  * [Pull request](./Documents/PullRequests.md)
    * [Setting up your local environment](./Documents/PullRequests.md#setting-up-your-local-environment)
    * [Making Changes](./Documents/PullRequests.md#making-changes)
    * [How to add card](./Documents/HowToAddCard.md)
    * [How to add task](./Documents/HowToAddTask.md)

## Contact

You can contact me via e-mail (utilForever at gmail.com). I am always happy to answer questions or help with any issues you might have, and please be sure to share any additional work or your creations with me, I love seeing what other people are making.

## Sponsors

[![CppDepend](./Medias/Logos/CppDepend.png)](http://www.cppdepend.com)

## License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The class is licensed under the [Affero GPLv3 License](https://opensource.org/licenses/AGPL-3.0):

RosettaStone is based on part of Sabberstone's code

Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva

RosettaStone is based on part of hearthstone-ai's code

Copyright (c) 2017 Peter Shih, peter1591

RosettaStone, Hearthstone simulator using C++ with some reinforcement learning

Copyright (c) 2017-2021 RosettaStone Team

  * [Chris Ohk](http://www.github.com/utilForever)
  * [Youngjoong Kim](https://github.com/revsic)
  * [Seunghyun Jeon](https://github.com/FuZer)
  * [Hyeongchan Kim](https://github.com/kozistr)
  * [Yoohan Park](https://github.com/CreatorSeraph)
  * [Hyeonsu Kim](https://github.com/git-rla)
  * [Junyeong Park](https://github.com/JYPark09)
  * [Sunghwan Kim](https://github.com/FYLSunghwan)
  * [Kyounguk Chae](https://github.com/ShyRoute)
  * [Junryung Ju](https://github.com/ArtBlnd)
  * [Beomgyu Kim](https://github.com/solarmagic)
  * [Doun Lee](https://github.com/Rayiz3)
  * [Ingyun Ahn](https://github.com/goltong1)
  * [Cheolwan Park](https://github.com/Cheolwan-Park)

RosettaStone is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License. RosettaStone is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.

Hearthstone is an interactive game of Blizzard Entertainment, Inc and all rights reserved. Hearthstone is a registered trademark of Blizzard Entertainment, Inc. in the U.S. and/or other countries. This project is not affiliated with Blizzard Entertainment.
