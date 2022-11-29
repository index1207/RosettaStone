// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSSETASTONE_ROSETTA_HPP
#define ROSSETASTONE_ROSETTA_HPP

#include <Rosetta/Battlegrounds/Actions/Generic.hpp>
#include <Rosetta/Battlegrounds/CardSets/BattlegroundsCardsGen.hpp>
#include <Rosetta/Battlegrounds/Cards/Card.hpp>
#include <Rosetta/Battlegrounds/Cards/CardDef.hpp>
#include <Rosetta/Battlegrounds/Cards/CardDefs.hpp>
#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Battlegrounds/Cards/TargetingPredicates.hpp>
#include <Rosetta/Battlegrounds/Conditions/SelfCondition.hpp>
#include <Rosetta/Battlegrounds/Enchants/Effect.hpp>
#include <Rosetta/Battlegrounds/Enchants/Effects.hpp>
#include <Rosetta/Battlegrounds/Enchants/Enchant.hpp>
#include <Rosetta/Battlegrounds/Enchants/Enchants.hpp>
#include <Rosetta/Battlegrounds/Enchants/Power.hpp>
#include <Rosetta/Battlegrounds/Games/Game.hpp>
#include <Rosetta/Battlegrounds/Games/GameState.hpp>
#include <Rosetta/Battlegrounds/Loaders/CardLoader.hpp>
#include <Rosetta/Battlegrounds/Loaders/InternalCardLoader.hpp>
#include <Rosetta/Battlegrounds/Managers/GameManager.hpp>
#include <Rosetta/Battlegrounds/Models/Battle.hpp>
#include <Rosetta/Battlegrounds/Models/Hero.hpp>
#include <Rosetta/Battlegrounds/Models/Minion.hpp>
#include <Rosetta/Battlegrounds/Models/MinionPool.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Battlegrounds/Models/Spell.hpp>
#include <Rosetta/Battlegrounds/Models/Tavern.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/AttackTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/CountTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/DamageHeroTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/GetGameTagTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/RandomTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/ReduceTavernCostTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/RepeatNumberEndTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/RepeatNumberStartTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/SetGameTagTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/SummonTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/TaskStack.hpp>
#include <Rosetta/Battlegrounds/Tasks/TaskType.hpp>
#include <Rosetta/Battlegrounds/Triggers/Trigger.hpp>
#include <Rosetta/Battlegrounds/Utils/GameUtils.hpp>
#include <Rosetta/Battlegrounds/Zones/FieldZone.hpp>
#include <Rosetta/Battlegrounds/Zones/HandZone.hpp>
#include <Rosetta/Common/Constants.hpp>
#include <Rosetta/Common/Enums/AuraEnums.hpp>
#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/Common/Enums/ChoiceEnums.hpp>
#include <Rosetta/Common/Enums/ConditionEnums.hpp>
#include <Rosetta/Common/Enums/GameEnums.hpp>
#include <Rosetta/Common/Enums/TargetingEnums.hpp>
#include <Rosetta/Common/Enums/TaskEnums.hpp>
#include <Rosetta/Common/Enums/TriggerEnums.hpp>
#include <Rosetta/Common/Macros.hpp>
#include <Rosetta/Common/PriorityQueue.hpp>
#include <Rosetta/Common/SpinLocks.hpp>
#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Actions/Attack.hpp>
#include <Rosetta/PlayMode/Actions/CastSpell.hpp>
#include <Rosetta/PlayMode/Actions/Choose.hpp>
#include <Rosetta/PlayMode/Actions/Copy.hpp>
#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Actions/PlayCard.hpp>
#include <Rosetta/PlayMode/Actions/Summon.hpp>
#include <Rosetta/PlayMode/Agents/IAgent.hpp>
#include <Rosetta/PlayMode/Agents/RandomAgent.hpp>
#include <Rosetta/PlayMode/Auras/AdaptiveCostEffect.hpp>
#include <Rosetta/PlayMode/Auras/AdaptiveEffect.hpp>
#include <Rosetta/PlayMode/Auras/AdjacentAura.hpp>
#include <Rosetta/PlayMode/Auras/Aura.hpp>
#include <Rosetta/PlayMode/Auras/AuraUpdateInstruction.hpp>
#include <Rosetta/PlayMode/Auras/EnrageEffect.hpp>
#include <Rosetta/PlayMode/Auras/IAura.hpp>
#include <Rosetta/PlayMode/Auras/SummoningPortalAura.hpp>
#include <Rosetta/PlayMode/Auras/SwitchingAura.hpp>
#include <Rosetta/PlayMode/CardSets/AlteracValleyCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/BlackTempleCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/BoomsdayCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/BrmCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/CoreCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/DalaranCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/DarkmoonFaireCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/DemonHunterInitCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/DragonsCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/Expert1CardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/GangsCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/GilneasCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/GvgCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/IcecrownCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/KaraCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/LegacyCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/LoECardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/LootapaloozaCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/NaxxCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/OgCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/Placeholder202204CardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/ReturnOfTheLichKingCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/RevendrethCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/ScholomanceCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/StormwindCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/TgtCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/TheBarrensCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/TheSunkenCityCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/TrollCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/UldumCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/UngoroCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/VanillaCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/YoDCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/Card.hpp>
#include <Rosetta/PlayMode/Cards/CardDef.hpp>
#include <Rosetta/PlayMode/Cards/CardDefs.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>
#include <Rosetta/PlayMode/Cards/CardProperty.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Conditions/RelaCondition.hpp>
#include <Rosetta/PlayMode/Conditions/SelfCondition.hpp>
#include <Rosetta/PlayMode/Decks/Deck.hpp>
#include <Rosetta/PlayMode/Enchants/Attrs/Atk.hpp>
#include <Rosetta/PlayMode/Enchants/Attrs/Attr.hpp>
#include <Rosetta/PlayMode/Enchants/Attrs/BoolAttr.hpp>
#include <Rosetta/PlayMode/Enchants/Attrs/Cost.hpp>
#include <Rosetta/PlayMode/Enchants/Attrs/Health.hpp>
#include <Rosetta/PlayMode/Enchants/Attrs/IntAttr.hpp>
#include <Rosetta/PlayMode/Enchants/Attrs/SelfContainedBoolAttr.hpp>
#include <Rosetta/PlayMode/Enchants/Attrs/SelfContainedIntAttr.hpp>
#include <Rosetta/PlayMode/Enchants/AuraEffects.hpp>
#include <Rosetta/PlayMode/Enchants/Effect.hpp>
#include <Rosetta/PlayMode/Enchants/Effects.hpp>
#include <Rosetta/PlayMode/Enchants/Enchant.hpp>
#include <Rosetta/PlayMode/Enchants/Enchants.hpp>
#include <Rosetta/PlayMode/Enchants/GenericEffect.hpp>
#include <Rosetta/PlayMode/Enchants/IEffect.hpp>
#include <Rosetta/PlayMode/Enchants/OngoingEnchant.hpp>
#include <Rosetta/PlayMode/Enchants/PlayerAuraEffects.hpp>
#include <Rosetta/PlayMode/Enchants/Power.hpp>
#include <Rosetta/PlayMode/Enchants/SwapCostEnchant.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Games/GameConfig.hpp>
#include <Rosetta/PlayMode/Loaders/CardLoader.hpp>
#include <Rosetta/PlayMode/Loaders/InternalCardLoader.hpp>
#include <Rosetta/PlayMode/Loaders/TargetingPredicates.hpp>
#include <Rosetta/PlayMode/Logs/PlayHistory.hpp>
#include <Rosetta/PlayMode/Managers/CostManager.hpp>
#include <Rosetta/PlayMode/Managers/GameManager.hpp>
#include <Rosetta/PlayMode/Managers/TriggerEvent.hpp>
#include <Rosetta/PlayMode/Managers/TriggerEventHandler.hpp>
#include <Rosetta/PlayMode/Managers/TriggerManager.hpp>
#include <Rosetta/PlayMode/Models/Character.hpp>
#include <Rosetta/PlayMode/Models/Choice.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Models/Entity.hpp>
#include <Rosetta/PlayMode/Models/Hero.hpp>
#include <Rosetta/PlayMode/Models/HeroPower.hpp>
#include <Rosetta/PlayMode/Models/Location.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Models/Placeable.hpp>
#include <Rosetta/PlayMode/Models/Playable.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Models/Spell.hpp>
#include <Rosetta/PlayMode/Models/Weapon.hpp>
#include <Rosetta/PlayMode/Tasks/ComplexTask.hpp>
#include <Rosetta/PlayMode/Tasks/ComplexTrigger.hpp>
#include <Rosetta/PlayMode/Tasks/EventMetaData.hpp>
#include <Rosetta/PlayMode/Tasks/ITask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/AttackTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/ChooseTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/EndTurnTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/HeroPowerTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/TradeCardTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ActivateCapturedDeathrattleTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ActivateDeathrattleTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/AddAuraEffectTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/AddCardTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/AddLackeyTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/AddPoisonTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/AddStackToTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ApplyEffectTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ArmorTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/AttackTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/CastCopyTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/CastRandomSpellTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/CastSpellStackTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ChanceTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ChangeAttackingTargetTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ChangeEntityTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ChangeHeroPowerTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ChangeUnidentifiedTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ClearStackTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ConditionTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ConsecutiveDamageTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ControlTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/CopyTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/CountTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/CustomTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DamageNumberTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DamageWeaponTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DestroyAllTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DestroyDeckCardTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DestroySoulFragmentTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DestroyTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DiscardTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DiscoverTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawMinionTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawNumberTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawOpTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawRaceMinionTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawSpellTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawStackTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawWeaponTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DredgeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/EnqueueNumberTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/EnqueueTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/FilterStackTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/FlagTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/FreezeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/FuncNumberTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/FuncPlayableTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/GetEventNumberTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/GetGameTagTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/GetPlayerGameTagTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/GetPlayerManaTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/HealFullTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/HealNumberTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/HealTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeAdjacentTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/InvokeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ManaCrystalTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/MathAddTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/MathMultiplyTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/MathNumberIndexTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/MathRandTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/MathSubtractTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/MoveToDeckTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/MoveToGraveyardTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/MoveToSetasideTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/NumberConditionTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/PlayTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/PutCardDeckTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/QuestProgressTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RandomCardTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RandomEntourageTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RandomMinionNumberTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RandomMinionTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RandomSpellTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RandomTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RefreshManaTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RemoveDurabilityTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RemoveEnchantmentTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RemoveHandTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ReplaceHeroTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ReturnHandTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RevealStealthTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SetGameTagNumberTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SetGameTagTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SetManaCrystalTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SetPlayerGameTagTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SilenceTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonCapturedMinionTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonCopyTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonNumberTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonOpTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonStackTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SwapAttackHealthTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SwapHeroPowerTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SwapTopCardTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/TempManaTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/TransformCopyTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/TransformMinionTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/TransformTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/WeaponStackTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/WeaponTask.hpp>
#include <Rosetta/PlayMode/Tasks/TaskQueue.hpp>
#include <Rosetta/PlayMode/Tasks/TaskStack.hpp>
#include <Rosetta/PlayMode/Triggers/MultiTrigger.hpp>
#include <Rosetta/PlayMode/Triggers/Trigger.hpp>
#include <Rosetta/PlayMode/Triggers/Triggers.hpp>
#include <Rosetta/PlayMode/Utils/DeckCode.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/IZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>
#include <Rosetta/PlayMode/Zones/Zone.hpp>
#include <Rosetta/RosettaStone.hpp>

#endif  // ROSSETASTONE_ROSETTA_HPP
