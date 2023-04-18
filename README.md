# ContextFramework

Custom ECS framework for Unreal Engine

This is very early still WIP

# Context Framework: Core

## Data Types:

**FCF_Context**: Entity in ECS each Context is unique and holds data as a map of Components

**FCF_Component**: each component type either holds mutable or imutable data for the context they are stored in components can be used as flags for checking 


## Functionality:



**UCF_Core:** static function library that can be used to create and remove contexts and set or remove components from contexts


**UCF_CoreSubsystem:** game instance subsystem that stores and handles context and component actions internaly this subsystem is used internaly in UCF_Core


## UnrealEngine Binding:

ACF_ActorWrapper : this and all Wrapper types can be bound to a context using the unigue id stored on them they allow calling functions within the heirarchy of these objects to access their bound context without using the context id


# Context Framework: Events

## Data Types:

**FCF_Message:** base data type for messages sent through the  event system

## Functionality:



**UCF_EventStatics:** static function library that can be used to Listen to or send messages localy or through the network


**UCF_EventSubsystem:** game instance subsystem that stores listeners to events and fires events on those listeners on the instance it is run on


## ENetworkMessageMode:

- **FromServerToAllClients**: this message will be broadcasted localy. it will also fire on all clients through GameState

- **FromServerToSepcificClient**: this message will be broadcasted localy. it will also fire on the specific client using PlayerId through Their PlayerState

- **FromClientToServer**: this message will be broadcasted localy. it will also fire on the the server using the invoker clients PlayerState. the player state can also be used as an authentication to use the event or not


## Details:

**DoubleMessageTypeEvents:** without the ability to template message types for component types for general events that could or should be fired based on another data type (eg component type) we use double message types to handle these kind of events so for example listening to if FSampleComponent has ben set for any context we Use a combination of FCF_ComponentSetMessageBase and FSampleComponent to listen to this.

# ContextFramework: Groups

Groups are designed to make it easier to query specific contexts that share single or several component types and cache that query for later use. 
They also allow for singleton type access to data in the form of components when the group only has a single context in it

## Data Types: 

**UCF_GroupStatics**: static function library used to access group functionalities such as getting and setting singleton components and getting group contexts. you can also set singleton components using a singleton component type. so when a contexts has a specific singleton component type as flag the developer can set components on that context using the flag component type


**Example usage:** we use FC_SB_IsPlayerContext component to flag contexts that hold player data we can use this component to access the group of contexts that have this component. the first time a group is requested it will search all contexts to create group. after the first time the group will automatically update when this component type is set or removed from contexts and accessing the group will not result in a search.

to create groups earlier we can have subsystems that initialize these groups so the initial search will be easier


# Context Framework: Systems

There is no specific type to use when trying to write systems for the context framework but a certain method has been used to make it easy.

For creating Systems we use Unreal Engine's Subsystems and place them in the module the subsystem should be initialized on and inherit from the special subsystem classes made for that submodule. this inheritance is to prevent subsystems from loading on incorrect instances in Play In Editor mode.

US_CO_GameInstanceSubsystem: for client systems

US_SO_GameInstanceSubsystem for server systems

A system will generaly listen to an event when initialized and run logic when that event is called. when there are several systems that want to subscribe to the same event it is better to create a ChainSystem that subscribes to the event and calls logic on the other several systems in the order intended by the developer. since those several systems are being called by the chain event they shouldnt subscribe to any event when initialized
