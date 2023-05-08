import 'package:bloc/bloc.dart';
import 'package:equatable/equatable.dart';

part 'points_event.dart';
part 'points_state.dart';

class PointsBloc extends Bloc<PointsEvent, PointsState> {
  PointsBloc() : super(PointsInitial()) {
    on<PointsRequestedEvent>((event, emit) {});
  }
}
