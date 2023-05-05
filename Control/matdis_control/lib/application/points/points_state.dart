part of 'points_bloc.dart';

abstract class PointsState extends Equatable {
  const PointsState();
  
  @override
  List<Object> get props => [];
}

class PointsInitial extends PointsState {}
