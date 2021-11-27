#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include"RPGHad.h"

int main(int argc,char*argv[]){
  int select=0,turn=0,flag=0,ret,c,end;
  char myname[256];

  printf("初めから>0,続きから>1 >>");//セーブデータの使用の確認
  scanf("%d",&select);

  //セーブロード
  if(select==1){DataLoad();}
  //新規作成
  else{NewGame();}

  //ゲームの終了が選択されるまでループ
  while(1){
    printf("\n");
    turn=0;

    EnemySelect();//敵のランダム選択

    EnterGo();//エンターキー遷移
    printf("\n");
    end=0;

    while(end==0){//戦闘が終了するまでループ

      select=BattleMenue();//選択肢の表示と行動選択

      if(select==1){//たたかう選択時
        ret=Attack();//こうげきの処理、ターンが終了した時1が返る
        turn+=ret;//次のターン(敵のターン)へ
      }
      else if(select==2){//まほう選択時
        ret=Magic();//まほうの処理、ターンが終了した時1が返る
        turn+=ret;//次のターン(敵のターン)へ
      }
      else if(select==3){//アイテム選択時
        ret=ItemUse();//アイテムの処理、ターンが終了した時1が返る
        turn+=ret;//次のターン(敵のターン)へ
      }
      else if(select==4){//逃げる選択時
        ret=Leave();//逃げるの処理、成功した時、2が返る
        if(ret==2){//逃げるの成功時
          flag=1;//勝利せず戦闘を終了した時のフラグ
          break;//戦闘処理の終了
        }
        else{turn+=ret;}//逃げるの失敗時、次のターン(敵のターン)へ
      }

      EnterGo();//エンターキー遷移


      if(GetEnemyHp()<=0){//敵撃破判定
        PrintEnemyName();//敵の名前の表示
        printf("は倒れた\n");
        flag=0;//勝利し、戦闘を終了した時のフラグ
        break;
      }

      //相手のターン
      if(turn%2==1){//相手のターンの時
        ret=EnemyAttack();//敵の攻撃、1が返ってくる
        turn+=ret;//次のターン(プレイヤーのターン)へ
      }

      if(GetMyHp()<=0){//プレイヤーがやられた時
        LoseResult();//敗北時の処理
        flag=1;//勝利せず戦闘を終了した時のフラグ
        break;//戦闘処理の終了
      }

      EnterGo();//エンターキー遷移

    }

    if(flag==0){Result();}//勝利時の処理

    EnterGo();//エンターキー遷移

    DataSave();//ゲームの進行状況をセーブ


    while(1){//戦闘終了時の処理
      ret=EndMenue();//戦闘終了時の選択肢の表示と行動選択
      if(ret==1||ret==0){break;}
    }

    if(ret==0){break;}//ゲームの終了を選択した時
  }
  return 0;
}
