part of 'points_bloc.dart';

abstract class PointsEvent extends Equatable {
  const PointsEvent();

  @override
  List<Object> get props => [];
}

///event when user presses reset button
class PointsResetRequestedEvent extends PointsEvent {
  final int pointsFieldId;
  const PointsResetRequestedEvent({required this.pointsFieldId});
}

///event when user presses reset button
class PointsAddRequestedEvent extends PointsEvent {
  final int pointsFieldId;
  const PointsAddRequestedEvent({required this.pointsFieldId});
}

///event when user presses reset button
class PointsRemoveRequestedEvent extends PointsEvent {
  final int pointsFieldId;
  const PointsRemoveRequestedEvent({required this.pointsFieldId});
}
