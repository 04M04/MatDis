import 'package:matdis_control/domain/entities/advicer_entity.dart';
import 'package:matdis_control/domain/failures/failures.dart';
import 'package:matdis_control/domain/usecases/advicer_usecases.dart';
import 'package:bloc/bloc.dart';
import 'package:dartz/dartz.dart';
import 'package:equatable/equatable.dart';
import 'package:flutter/material.dart';

part 'advicer_event.dart';
part 'advicer_state.dart';

const generalFailureMessage =
    "Oops, something has gone wrong. Please try again!";
const serverFailureMessage = "Oops, API-Error. Please try again!";

class AdvicerBloc extends Bloc<AdvicerEvent, AdvicerState> {
  final AdvicerUsecases advicerUsecases;
  AdvicerBloc({required this.advicerUsecases}) : super(AdvicerInitial()) {
    on<AdviceRequestedEvent>((event, emit) async {
      emit(AdvicerStateLoading());

      Either<Failure, AdviceEntity> adviceOrFailure =
          await advicerUsecases.getAdviceUsecase();

      adviceOrFailure.fold(
          (failure) =>
              emit(AdvicerStateError(message: _mapFailureToMessage(failure))),
          (advice) => emit(AdvicerStateLoaded(advice: advice.advice)));
    });
  }

  String _mapFailureToMessage(Failure failure) {
    switch (failure.runtimeType) {
      case ServerFailure:
        return serverFailureMessage;
      case GeneralFailure:
        return generalFailureMessage;
      default:
        return generalFailureMessage;
    }
  }
}
