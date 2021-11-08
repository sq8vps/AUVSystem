#include "Debug.h"

#include <bitset>
#include <vector>

#include "ROSEnums.h"

void Debug::processInMainLoop()
{
	if( ticks % debugTickSpan == 0 )
	{
		ros::master::getTopics( listOfTopics );

		displayer.displayDebugInfo( this->countAndCompareNumberOfTopics() );
	}
}

void Debug::subscribeTopics()
{
	displayer.addInfoToDisplay(
	    "Health Info", std::vector< std::string >( AUVROS::NodeNames.begin(), AUVROS::NodeNames.end() ), "init" );
	this->rosSubscribers.emplace_back( this->rosNode->subscribe( AUVROS::Topics::Health::healthReportSummary,
	                                                             AUVROS::QueueSize::GlobalHealthQueueSize,
	                                                             &Debug::displayNodeHealthStatus,
	                                                             this ) );
																 displayer.addInfoToDisplay(
	    "Health Info", std::vector< std::string >( AUVROS::NodeNames.begin(), AUVROS::NodeNames.end()-5 ), "init" );
	
}

void Debug::displayNodeHealthStatus( const AUVROS::MessageTypes::HealthReport& report )
{
	std::vector< DataType > values;

	std::bitset< AUVROS::NodeIDs::Count > nodesHealthSet( report.data );

	for( int i = 0; i < nodesHealthSet.size(); ++i )
	{
		if( nodesHealthSet[ i ] == 1 )
		{
			values.emplace_back( "healthy" );
		}
		else
		{
			values.emplace_back( "down" );
		}
	}
	displayer.setMajorColumnValues( DisplayerDataPositions::Health, values );
}

void Debug::advertiseTopics() {}
void Debug::connectServices() {}

bool Debug::countAndCompareNumberOfTopics() const
{
	unsigned countActive;
	for( auto& in : listOfTopics )
	{
		if( in.name.find( AUVROS::Folders::MainFolderShort ) != std::string::npos )
		{
			++countActive;
		}
	}
	return ( countActive == ( this->rosSubscribers.size() - this->numberofIgnoredTopics ) );
}
