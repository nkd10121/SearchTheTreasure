#pragma once
#include "DxLib.h"
#include <string>
#include <vector>
#include <map>
#include <array>

class DataLoader
{
public:
	/// <summary>
	/// ステージデータ
	/// </summary>
	struct stageData
	{
		std::vector<int> mapData;					//マップの配列
		VECTOR startPos = VGet(0.0f,0.0f,0.0f);		//スタート座標
		VECTOR clearPos = VGet(0.0f, 0.0f, 0.0f);	//クリア座標
		float chestDir = 0.0f;						//チェストの向き
	};

	/// <summary>
	/// 読み込むcsvの並び順
	/// NOTE:読み込む情報を増やすたびにここに追加する必要あり
	/// </summary>
	enum eStageDataOrder : int
	{
		stageName,		//ステージ名
		mapDataPath,	//マップデータが入ったcsvのパス
		startPosX,		//スタートX座標
		startPosZ,		//スタートZ座標
		clearPosX,		//クリアX座標
		clearPosZ,		//クリアZ座標
		chestDir		//チェストの向き
	};

	/// <summary>
	/// ステージデータのロード
	/// </summary>
	void StageLoad();

	/// <summary>
	/// マップデータを返す
	/// </summary>
	/// <returns>マップデータ</returns>
	const std::map <std::string, stageData> GetStageData()const { return m_stageData; };

	/// <summary>
	/// ステージ名一覧を返す
	/// </summary>
	/// <returns>ステージ名一覧</returns>
	const std::vector<std::string> GetStageName()const { return m_stageName; };

private:

	/// <summary>
	/// ひとつにまとめられた読み込んだ情報をカンマ区切りにわける
	/// </summary>
	/// <param name="str">ひとつにまとめられた読み込んだ情報</param>
	/// <param name="del">区切る地点となる文字</param>
	/// <returns></returns>
	std::vector<std::string> Split(std::string& str, char del);	

	/// <summary>
	/// マップデータを読み込む
	/// </summary>
	/// <param name="inputData">読み込まれた情報群</param>
	/// <param name="stageName">情報を入れるステージ名</param>
	void LoadMiniMapData(std::vector<std::string>& inputData, std::string stageName);

private:
	std::map <std::string, stageData> m_stageData;	//マップデータ
	std::vector<std::string> m_stageName;			//ステージ名一覧
};

