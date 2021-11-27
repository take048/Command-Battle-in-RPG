#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"RPGHad.h"

FILE *fp,*mfp,*ifp,*sfp,*isfp,*rifp;
int i,esele,end=0,select=0,eact,turn=0,flag=0;
int playerSt[9]={1,0,0,0,0,0,0,0,0};//プレイヤーのステータス
//0:レベル, 1:経験値, 2:最大HP, 3:HP, 4:最大MP, 5:MP, 6:攻撃力, 7:攻撃力, 8:魔法レベル
int enemySt[5]={0,0,0,0,0};//敵のステータス
//0:敵ID, 1:敵撃破時の獲得経験値, 2:敵のHP, 3:敵の攻撃力, 4:敵の防御力
int act;
int lostmp,mgup,mglow,mgskil=0,inum=0,effnum,drop,get,ret,c;
char ename[256],myname[256],mgname[256],itname[256],effname[256];


//セーブデータのロード
void DataLoad(){
  sfp=fopen("save.txt","r+");
  fscanf(sfp,"%s",myname);
  fscanf(sfp,"%d",&playerSt[2]);
  playerSt[3]=playerSt[2];
  fscanf(sfp,"%d",&playerSt[4]);
  playerSt[5]=playerSt[4];
  fscanf(sfp,"%d",&playerSt[6]);
  fscanf(sfp,"%d",&playerSt[7]);
  fscanf(sfp,"%d",&playerSt[0]);
  fscanf(sfp,"%d",&playerSt[1]);
  fscanf(sfp,"%d",&playerSt[8]);
  fclose(sfp);
}

//セーブデータ新規作成
void NewGame(){
  printf("あなたの名前は：");
  scanf("%s",myname);
  //プレイヤーステータスのランダム生成
  playerSt[2]=randomre(20,15);
  playerSt[3]=playerSt[2];
  playerSt[6]=randomre(5,3);
  playerSt[7]=randomre(5,3);
  playerSt[4]=randomre(15,10);
  playerSt[5]=playerSt[4];
  //セーブデータの保存
  sfp=fopen("save.txt","r+");
  fprintf(sfp,"%s\n",myname);
  fprintf(sfp,"%d\n",playerSt[2]);
  fprintf(sfp,"%d\n",playerSt[4]);
  fprintf(sfp,"%d\n",playerSt[6]);
  fprintf(sfp,"%d\n",playerSt[7]);
  fprintf(sfp,"%d\n",playerSt[0]);
  fprintf(sfp,"%d\n",playerSt[1]);
  fprintf(sfp,"%d\n",playerSt[8]);
  fclose(sfp);
  //アイテム情報の初期化
  ifp=fopen("item.txt","w");
  rifp=fopen("initItem.txt","r");
  while(1){
    fscanf(rifp,"%s",itname);
    fscanf(rifp,"%s",effname);
    fscanf(rifp,"%d",&inum);
    fprintf(ifp,"%s\n",itname);
    fprintf(ifp,"%s\n",effname);
    fprintf(ifp,"%d\n",inum);
    if(inum==-1){break;}
  }
  fclose(ifp);
  fclose(isfp);
}

//敵の選択
void EnemySelect(){
  //プレイヤーのレベルを基準に敵をランダムに選択
  esele=playerSt[0]/2;
  if(esele<=0){esele=1;}
  if(esele>10){esele=10;}
  i=randomre(esele,1);

  //敵のデータをロード
  fp=fopen("enemy.txt","r");
  while(i!=0){
    fscanf(fp,"%d",&enemySt[0]);
    fscanf(fp,"%s",ename);
    fscanf(fp,"%d",&enemySt[2]);
    fscanf(fp,"%d",&enemySt[3]);
    fscanf(fp,"%d",&enemySt[4]);
    fscanf(fp,"%d",&enemySt[1]);
    i--;
  }
  printf("-------------------------\n");
  printf("%sが現れた\n",ename);
  printf("-------------------------\n");
}

//プレイヤーの行動選択肢の表示と選択
int BattleMenue(){
  printf("             -------------------------\n");
  printf("                     %s HP:%d\n\n",ename,enemySt[2]);
  printf("%s Lv.%d HP:%d/%d MP:%d/%d\n",myname,playerSt[0],playerSt[3],playerSt[2],playerSt[5],playerSt[4]);
  printf("----------------------\n");
  printf("たたかう>1 まほう>2 アイテム>3 にげる>4 >>");
  scanf("%d",&select);
  return select;
}

//プレイヤーの攻撃処理
int Attack(){
  printf("\n%sの攻撃\n",myname);
  act=randomre(playerSt[6]+1,playerSt[6]-1);//攻撃力+-1でダメージの決定
  act-=enemySt[4];//敵防御力によるダメージ時の現象
  if(act<=0){act=1;}//0以下の時1に変更
  enemySt[2]-=act;//敵のHPを減らす
  printf("%sに%dのダメージ\n\n",ename,act);
  ret=1;
  return ret;
}

//プレイヤーの魔法攻撃処理
int Magic(){
  if(playerSt[8]<=0){//魔法レベルが足りない時
    printf("まほうを覚えていません\n\n");
    ret=0;
  }
  else{
    //魔法データの呼び出し
    mfp=fopen("magic.txt","r");
    i=0;
    while(playerSt[8]>i){
      fscanf(mfp,"%s",mgname);
      fscanf(mfp,"%d",&lostmp);
      fscanf(mfp,"%d",&mgup);
      fscanf(mfp,"%d",&mglow);
      printf("%s(MP:%d)>%d\n",mgname,lostmp,i+1);
      i++;
    }
    //魔法の選択
    printf(">>");
    scanf("%d",&select);
    if(select!=0){
      mfp=fopen("magic.txt","r");
      while(select!=0){
        fscanf(mfp,"%s",mgname);
        fscanf(mfp,"%d",&lostmp);
        fscanf(mfp,"%d",&mgup);
        fscanf(mfp,"%d",&mglow);
        select--;
      }
      if(playerSt[5]-lostmp<0){//MPが足りない時
        printf("MPが足りません\n\n");
        ret=0;
      }
      else{
        playerSt[5]-=lostmp;//MPの消費
        act=randomre(mgup,mglow);//魔法ダメージの決定
        if(playerSt[4]>=50&&playerSt[4]<100){act=(playerSt[4]*0.02)*act;}
        else if(playerSt[4]>=100){act=(playerSt[4]*0.01)*act;}
        act-=enemySt[4];//敵防御力による魔法ダメージの減少
        if(act<=0){act=1;}//0以下の時1に変更
        enemySt[2]-=act;//敵のHPを減らす
        printf("%sを唱えた\n",mgname);
        printf("%sに%dのダメージ\n\n",ename,act);
        ret=1;
      }
    }
  }
  return ret;
}

//プレイヤーのアイテム使用時の処理
int ItemUse(){
  //所持アイテムの表示
  printf("\n");
  ifp=fopen("item.txt","r");
  isfp=fopen("itememo.txt","w");
  i=0;
  while(1){
    i++;
    fscanf(ifp,"%s",itname);
    fscanf(ifp,"%s",effname);
    fscanf(ifp,"%d",&inum);
    fprintf(isfp,"%s\n",itname);
    fprintf(isfp,"%s\n",effname);
    fprintf(isfp,"%d\n",inum);
    if(inum==-1){break;}
    printf("%s(HP%s回復):%d個 >>%d\n",itname,effname,inum,i);
  }
  printf("もどる >>0");
  fclose(isfp);
  fclose(ifp);


  //使用アイテムの選択
  i=0;
  printf("\nどれを使う?：");
  scanf("%d",&select);
  while(1){
    if(select==0){
      printf("\n");
      ret=0;
      break;
    }
    i=0;
    ifp=fopen("item.txt","r");
    while(1){
      fscanf(ifp,"%s",itname);
      fscanf(ifp,"%d",&effnum);
      fscanf(ifp,"%d",&inum);
      if(effnum==0){
        effnum=playerSt[2]-playerSt[3];
      }
      i++;
      if(select==i){break;}
    }

    if(inum<=0){//選択したアイテムがない時
      fclose(ifp);
      printf("そのアイテムはありません\n");
      printf("\nどれを使う?：");
      scanf("%d",&select);
    }
    else{
      fclose(ifp);
      break;
    }
  }
  playerSt[3]+=effnum;//HPの回復
  if(playerSt[3]>playerSt[2]){//HPの最大値を超えた場合の処理
    effnum-=playerSt[3]-playerSt[2];
    playerSt[3]=playerSt[2];
  }
  if(select!=0){
    printf("%d回復した\n\n",effnum);
    ret=1;
  }

  //使用アイテムの個数を減らす
  i=0;
  ifp=fopen("item.txt","w");
  isfp=fopen("itememo.txt","r");
  while(1){
    fscanf(isfp,"%s",itname);
    fscanf(isfp,"%s",effname);
    fscanf(isfp,"%d",&inum);
    if(select==i+1){inum-=1;}
    fprintf(ifp,"%s\n",itname);
    fprintf(ifp,"%s\n",effname);
    fprintf(ifp,"%d\n",inum);
    if(inum==-1){break;}
    i++;
  }

  fclose(ifp);
  fclose(isfp);
  return ret;
}

//プレイヤーの逃げる処理
int Leave(){
  i=randomre(4,0);//成功の判定をランダムに決定
  if(i==0){//失敗の時
    printf("\n逃げられない\n\n");
    ret=1;
  }
  else{//成功の時
    printf("\nなんとか逃げられた\n\n");
    flag=1;
    ret=2;
  }
  return ret;
}

//敵の攻撃処理
int EnemyAttack(){
  printf("%sの攻撃\n",ename);
  eact=randomre(enemySt[3]+2,enemySt[3]);//敵の講義期によるダメージの決定
  eact-=playerSt[7];//プレイヤーの防御力によるダメージの現象
  if(eact<=0){eact=1;}//0以下の時1に変更
  playerSt[3]-=eact;//プレイヤーのHPを減らす
  printf("%sに%dのダメージ\n\n",myname,eact);
  ret=1;
  return ret;
}

//戦闘勝利時の処理
void Result(){
  //ドロップアイテムの決定
  if(1<=enemySt[0]&&enemySt[0]<=4){drop=1;}
  if(5<=enemySt[0]&&enemySt[0]<=7){drop=2;}
  if(8<=enemySt[0]&&enemySt[0]<=10){drop=3;}
  get=randomre(drop,0);//アイテム取得判定

  //経験値の取得とレベルアップ処理
  printf("%sは経験値%d手に入れた\n",myname,enemySt[1]);
  playerSt[1]+=enemySt[1];
  while(playerSt[1]>=(playerSt[0]+1)*(playerSt[0]+1)){
    playerSt[1]-=(playerSt[0]+1)*(playerSt[0]+1);
    playerSt[0]++;
    playerSt[2]+=randomre(10,8);
    playerSt[3]=playerSt[2];
    playerSt[6]+=5;
    playerSt[7]+=5;
    playerSt[4]+=randomre(9,7);
    playerSt[5]=playerSt[4];
    printf("レベルアップ！！\n");
    printf("レベルが%dに上がった\n",playerSt[0]);
    if(playerSt[0]%4==0&&playerSt[8]<6){
      playerSt[8]++;
      printf("新しいまほうを覚えた\n");
    }
  }
  i=0;

  //アイテム取得処理
  if(get==0){
    ifp=fopen("item.txt","r");
    isfp=fopen("itememo.txt","w");
    while(1){
      fscanf(ifp,"%s",itname);
      fscanf(ifp,"%s",effname);
      fscanf(ifp,"%d",&inum);
      fprintf(isfp,"%s\n",itname);
      fprintf(isfp,"%s\n",effname);
      fprintf(isfp,"%d\n",inum);
      if(inum==-1){break;}
    }
    fclose(ifp);
    ifp=fopen("item.txt","r");
    while(1){
      i++;
      fscanf(ifp,"%s",itname);
      fscanf(ifp,"%s",effname);
      fscanf(ifp,"%d",&inum);
      if(drop==i){break;}
    }
    fclose(isfp);
    fclose(ifp);
    printf("%sを手に入れた\n",itname);
    i=0;
    ifp=fopen("item.txt","w");
    isfp=fopen("itememo.txt","r");
    while(1){
      fscanf(isfp,"%s",itname);
      fscanf(isfp,"%s",effname);
      fscanf(isfp,"%d",&inum);
      if(drop==i+1){inum+=1;}
      fprintf(ifp,"%s\n",itname);
      fprintf(ifp,"%s\n",effname);
      fprintf(ifp,"%d\n",inum);
      if(inum==-1){break;}
      i++;
    }
    fclose(ifp);
    fclose(isfp);
  }
}

//戦闘敗北時の処理
void LoseResult(){
  playerSt[2]-=10;
  playerSt[4]-=10;
  playerSt[3]=playerSt[2];
  playerSt[5]=playerSt[4];
  PrintPlayerName();
  printf("は倒れた\n");
  playerSt[0]-=1;
  playerSt[1]=0;
}

//ゲーム進行情報の保存処理
void DataSave(){
  sfp=fopen("save.txt","r+");
  fprintf(sfp,"%s\n",myname);
  fprintf(sfp,"%d\n",playerSt[2]);
  fprintf(sfp,"%d\n",playerSt[4]);
  fprintf(sfp,"%d\n",playerSt[6]);
  fprintf(sfp,"%d\n",playerSt[7]);
  fprintf(sfp,"%d\n",playerSt[0]);
  fprintf(sfp,"%d\n",playerSt[1]);
  fprintf(sfp,"%d\n",playerSt[8]);
  fclose(sfp);
}

//終了時メニュー
int EndMenue(){
  printf("\nもう一度遊びますか\nはい>>1 いいえ>>0 ステータスの確認>>2:");
  scanf("%d",&select);
  if(select==2){//ステータスの表示
    sfp=fopen("save.txt","r+");
    fscanf(sfp,"%s",myname);
    fscanf(sfp,"%d",&playerSt[2]);
    fscanf(sfp,"%d",&playerSt[4]);
    fscanf(sfp,"%d",&playerSt[6]);
    fscanf(sfp,"%d",&playerSt[7]);
    fscanf(sfp,"%d",&playerSt[0]);
    fscanf(sfp,"%d",&playerSt[1]);
    fscanf(sfp,"%d",&playerSt[8]);
    fclose(sfp);
    printf("\n%s Lv.%d HP:%d/%d MP:%d/%d 攻撃力:%d 防御力:%d\n",myname,playerSt[0],playerSt[3],playerSt[2],playerSt[5],playerSt[4],playerSt[6],playerSt[7]);
    printf("次のレベルまであと%d\n",(playerSt[0]+1)*(playerSt[0]+1)-playerSt[1]);
  }
  return select;
}

//プレイヤーのHPを返す
int GetMyHp(){
  return playerSt[3];
}
//敵のHPを返す
int GetEnemyHp(){
  return enemySt[2];
}
//プレイヤーの名前の表示
void PrintPlayerName(){
  printf("%s",myname);
}
//敵の名前の表示
void PrintEnemyName(){
  printf("%s",ename);
}

//ランダム用関数
int randomre(int most,int last){
  srand((unsigned int)time(NULL));
  return rand()%(most-last+1)+last;
}

//エンターキー遷移
void EnterGo(){
  printf("                      Please Enter");
  rewind(stdin);
  if ((c = getchar()) == '\n'){}
}
