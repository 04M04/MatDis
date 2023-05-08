part of 'points_bloc.dart';

abstract class PointsEvent extends Equatable {
  const PointsEvent();

  @override
  List<Object> get props => [];
}

///event when user presses add or remove button
class PointsRequestedEvent extends PointsEvent {
  
}

