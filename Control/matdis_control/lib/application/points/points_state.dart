part of 'points_bloc.dart';

abstract class PointsState extends Equatable {
  const PointsState();

  @override
  List<Object> get props => [];
}

///state when points count will be initialized
class PointsInitial extends PointsState {}

///state when new points count will be loaded from ble device
class PointsStateLoading extends PointsState {}

///state when new points count have loaded from ble device
class PointsStateLoaded extends PointsState {}

///state when new points count will be send to ble device
class PointsStateSend extends PointsState {}

///state when a error occurs
class PointsStateError extends PointsState {}

///state when a connecting to ble device
class PointsStateConnecting extends PointsState {}

///state when a connected to ble device
class PointsStateConnected extends PointsState {}
