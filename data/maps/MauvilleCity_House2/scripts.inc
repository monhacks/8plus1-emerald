MauvilleCity_House2_MapScripts::
	.byte 0

MauvilleCity_House2_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_COIN_CASE, MauvilleCity_House2_EventScript_ReceivedCoinCase
	msgbox MauvilleCity_House2_Text_BuyHarborMailAtSlateport, MSGBOX_DEFAULT
	checkitem ITEM_HARBOR_MAIL
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_House2_EventScript_AskToTradeForHarborMail
	release
	end

MauvilleCity_House2_EventScript_AskToTradeForHarborMail::
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox MauvilleCity_House2_Text_TradeHarborMailForCoinCase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_House2_EventScript_AcceptTrade
	goto_if_eq VAR_RESULT, NO, MauvilleCity_House2_EventScript_DeclineTrade
	end

MauvilleCity_House2_EventScript_AcceptTrade::
	msgbox MauvilleCity_House2_Text_IllTradeYouCoinCase, MSGBOX_DEFAULT
	removeitem ITEM_HARBOR_MAIL
	giveitem ITEM_COIN_CASE
	addcoins 100
	setflag FLAG_RECEIVED_COIN_CASE
	msgbox MauvilleCity_House2_Text_ExplainCoin, MSGBOX_DEFAULT
	goto MauvilleCity_House2_EventScript_ReceivedCoinCase
	end

MauvilleCity_House2_EventScript_ReceivedCoinCase::
	msgbox MauvilleCity_House2_Text_UseCoinCaseAtGameCorner, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House2_EventScript_DeclineTrade::
	msgbox MauvilleCity_House2_Text_ThatsDisappointing, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House2_Text_BuyHarborMailAtSlateport:
	.string "If I had a BIKE, it'd be easy to cycle to\n"
	.string "SLATEPORT for some shopping.\p"
	.string "I'd be able to buy HARBOR MAIL at the\n"
	.string "POKéMON MART in SLATEPORT…$"

MauvilleCity_House2_Text_TradeHarborMailForCoinCase:
	.string "Oh! You have HARBOR MAIL?\n"
	.string "Will you trade it for a COIN CASE?$"

MauvilleCity_House2_Text_IllTradeYouCoinCase:
	.string "Oh, I'm so happy!\n"
	.string "...\p"
	.string "Wait a second! You're underage!\n"
	.string "It's illegal to give you this!\p" 
	.string "Here, take this COIN WALLET instead!$"

MauvilleCity_House2_Text_ExplainCoin:
	.string "That COIN WALLET can be used\n"
	.string "to trade Cryptocurrency (COIN).\l"
	.string "Here, I'll give you 100 to start!$"

MauvilleCity_House2_Text_UseCoinCaseAtGameCorner:
	.string "Keep an eye on your investments,\n"
	.string "and you can get super rich!$"

MauvilleCity_House2_Text_ThatsDisappointing:
	.string "Oh, that's disappointing.\p"
	.string "A COIN CASE is needed for the\n"
	.string "GAME CORNER.$"

