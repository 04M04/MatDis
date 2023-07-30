import 'package:bloc/bloc.dart';
import 'package:equatable/equatable.dart';
import 'package:flutter/foundation.dart';

part 'points_event.dart';
part 'points_state.dart';

const generalFailureMessage =
    "There is some error!\nPlease ask your Administrator for help,\nor try again!";

class PointsBloc extends Bloc<PointsEvent, PointsState> {
  PointsBloc() : super(PointsInitial()) {
    Future sleep1() {
      return Future.delayed(const Duration(seconds: 1), () => "1");
    }

    ///event when user presses reset button
    on<PointsResetRequestedEvent>((event, emit) async {
      emit(PointsStateSend());
      await sleep1();
      //DOTO send reset command to ble device
      emit(PointsStateLoading());
      //DOTO get new points count from ble device
      emit(PointsStateLoaded());
      //DOTO send new points count to ui
      if (kDebugMode) {
        print("here is the data: ${event.pointsFieldId}");
      }
    });

    ///event when user presses add button
    on<PointsAddRequestedEvent>((event, emit) async {
      await sleep1();
      emit(PointsStateLoading());
      emit(PointsStateLoaded());
      emit(PointsStateSend());
      if (kDebugMode) {
        print("here is the data: ${event.pointsFieldId}");
      }
    });

    ///event when user presses remove button
    on<PointsRemoveRequestedEvent>((event, emit) async {
      await sleep1();
      emit(PointsStateLoading());
      emit(PointsStateLoaded());
      emit(PointsStateSend());
      if (kDebugMode) {
        print("here is the data: ${event.pointsFieldId}");
      }
    });

    ///event when user presses connect button
    on<ConnectToBluetoothDevice>((event, emit) async {
      emit(PointsStateLoading());
      emit(PointsStateLoaded());
      if (kDebugMode) {
        print("device name: ${event.deviceName}");
      }
    });
  }
}
